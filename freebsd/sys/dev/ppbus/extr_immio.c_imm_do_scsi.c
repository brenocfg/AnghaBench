#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpoio_data {int /*<<< orphan*/  vpo_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PPB_INTR ; 
 int /*<<< orphan*/  PPB_IN_EPP_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PPB_IN_NIBBLE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PPB_IN_PS2_MODE (int /*<<< orphan*/ ) ; 
 int PPB_WAIT ; 
 int VP0_ECMD_TIMEOUT ; 
 int VP0_ECONNECT ; 
 int VP0_EDATA_OVERFLOW ; 
 int VP0_ENEGOCIATE ; 
 int VP0_EOTHER ; 
 int VP0_EPPDATA_TIMEOUT ; 
 int VP0_ESTATUS_TIMEOUT ; 
 int /*<<< orphan*/  VP0_FAST_SPINTMO ; 
 int /*<<< orphan*/  VP0_LOW_SPINTMO ; 
 int VP0_SECTOR_SIZE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int imm_connect (struct vpoio_data*,int,int*,int) ; 
 int /*<<< orphan*/  imm_disconnect (struct vpoio_data*,int /*<<< orphan*/ *,int) ; 
 int imm_instr (struct vpoio_data*,char*,int) ; 
 scalar_t__ imm_negociate (struct vpoio_data*) ; 
 int imm_outstr (struct vpoio_data*,char*,int) ; 
 int imm_select (struct vpoio_data*,int,int) ; 
 char imm_wait (struct vpoio_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transfer_epilog ; 

int
imm_do_scsi(struct vpoio_data *vpo, int host, int target, char *command,
		int clen, char *buffer, int blen, int *result, int *count,
		int *ret)
{
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	char r;
	char l, h = 0;
	int len, error = 0, not_connected = 0;
	int k;
	int negociated = 0;

	/*
	 * enter disk state, allocate the ppbus
	 *
	 * XXX
	 * Should we allow this call to be interruptible?
	 * The only way to report the interruption is to return
	 * EIO to upper SCSI code :^(
	 */
	if ((error = imm_connect(vpo, PPB_WAIT|PPB_INTR, &not_connected, 1)))
		return (error);

	if (not_connected) {
		*ret = VP0_ECONNECT;
		goto error;
	}

	/*
	 * Select the drive ...
	 */
	if ((*ret = imm_select(vpo,host,target)))
		goto error;

	/*
	 * Send the command ...
	 */
	for (k = 0; k < clen; k+=2) {
		if (imm_wait(vpo, VP0_FAST_SPINTMO) != (char)0xa8) {
			*ret = VP0_ECMD_TIMEOUT;
			goto error;
		}
		if (imm_outstr(vpo, &command[k], 2)) {
			*ret = VP0_EPPDATA_TIMEOUT;
			goto error;
		}
	}

	if (!(r = imm_wait(vpo, VP0_LOW_SPINTMO))) {
		*ret = VP0_ESTATUS_TIMEOUT;
		goto error;
	}

	if ((r & 0x30) == 0x10) {
		if (imm_negociate(vpo)) {
			*ret = VP0_ENEGOCIATE;
			goto error;
		} else
			negociated = 1;
	}

	/*
	 * Complete transfer ...
	 */
	*count = 0;
	for (;;) {

		if (!(r = imm_wait(vpo, VP0_LOW_SPINTMO))) {
			*ret = VP0_ESTATUS_TIMEOUT;
			goto error;
		}

		/* stop when the ZIP+ wants to send status */
		if (r == (char)0xb8)
			break;

		if (*count >= blen) {
			*ret = VP0_EDATA_OVERFLOW;
			goto error;
		}

		/* ZIP+ wants to send data? */
		if (r == (char)0x88) {
			len = (((blen - *count) >= VP0_SECTOR_SIZE)) ?
				VP0_SECTOR_SIZE : 2;

			error = imm_outstr(vpo, &buffer[*count], len);
		} else {
			if (!PPB_IN_EPP_MODE(ppbus))
				len = 1;
			else
				len = (((blen - *count) >= VP0_SECTOR_SIZE)) ?
					VP0_SECTOR_SIZE : 1;

			error = imm_instr(vpo, &buffer[*count], len);
		}

		if (error) {
			*ret = error;
			goto error;
		}

		*count += len;
	}

	if ((PPB_IN_NIBBLE_MODE(ppbus) ||
			PPB_IN_PS2_MODE(ppbus)) && negociated)
		ppb_MS_microseq(ppbus, vpo->vpo_dev, transfer_epilog, NULL);

	/*
	 * Retrieve status ...
	 */
	if (imm_negociate(vpo)) {
		*ret = VP0_ENEGOCIATE;
		goto error;
	} else
		negociated = 1;

	if (imm_instr(vpo, &l, 1)) {
		*ret = VP0_EOTHER;
		goto error;
	}

	/* check if the ZIP+ wants to send more status */
	if (imm_wait(vpo, VP0_FAST_SPINTMO) == (char)0xb8)
		if (imm_instr(vpo, &h, 1)) {
			*ret = VP0_EOTHER + 2;
			goto error;
		}

	/* Experience showed that we should discard this */
	if (h == (char) -1)
		h = 0;

	*result = ((int) h << 8) | ((int) l & 0xff);

error:
	if ((PPB_IN_NIBBLE_MODE(ppbus) ||
			PPB_IN_PS2_MODE(ppbus)) && negociated)
		ppb_MS_microseq(ppbus, vpo->vpo_dev, transfer_epilog, NULL);

	/* return to printer state, release the ppbus */
	imm_disconnect(vpo, NULL, 1);

	return (0);
}