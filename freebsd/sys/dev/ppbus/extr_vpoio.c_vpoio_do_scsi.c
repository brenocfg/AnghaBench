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
 int H_AUTO ; 
 int H_INIT ; 
 int H_STROBE ; 
 int H_nSELIN ; 
 int PPB_INTR ; 
 scalar_t__ PPB_IN_EPP_MODE (int /*<<< orphan*/ ) ; 
 int PPB_WAIT ; 
 int VP0_ECMD_TIMEOUT ; 
 int VP0_ECONNECT ; 
 int VP0_EDATA_OVERFLOW ; 
 int VP0_EOTHER ; 
 int VP0_EPPDATA_TIMEOUT ; 
 int VP0_ESTATUS_TIMEOUT ; 
 int /*<<< orphan*/  VP0_FAST_SPINTMO ; 
 int /*<<< orphan*/  VP0_LOW_SPINTMO ; 
 int VP0_SECTOR_SIZE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 
 int vpoio_connect (struct vpoio_data*,int) ; 
 int /*<<< orphan*/  vpoio_disconnect (struct vpoio_data*) ; 
 int /*<<< orphan*/  vpoio_in_disk_mode (struct vpoio_data*) ; 
 int vpoio_instr (struct vpoio_data*,char*,int) ; 
 int vpoio_outstr (struct vpoio_data*,char*,int) ; 
 int vpoio_select (struct vpoio_data*,int,int) ; 
 char vpoio_wait (struct vpoio_data*,int /*<<< orphan*/ ) ; 

int
vpoio_do_scsi(struct vpoio_data *vpo, int host, int target, char *command,
		int clen, char *buffer, int blen, int *result, int *count,
		int *ret)
{
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	char r;
	char l, h = 0;
	int len, error = 0;
	int k;

	/*
	 * enter disk state, allocate the ppbus
	 *
	 * XXX
	 * Should we allow this call to be interruptible?
	 * The only way to report the interruption is to return
	 * EIO do upper SCSI code :^(
	 */
	if ((error = vpoio_connect(vpo, PPB_WAIT|PPB_INTR)))
		return (error);

	if (!vpoio_in_disk_mode(vpo)) {
		*ret = VP0_ECONNECT;
		goto error;
	}

	if ((*ret = vpoio_select(vpo,host,target)))
		goto error;

	/*
	 * Send the command ...
	 *
	 * set H_SELIN low for vpoio_wait().
	 */
	ppb_wctr(ppbus, H_AUTO | H_nSELIN | H_INIT | H_STROBE);

	for (k = 0; k < clen; k++) {
		if (vpoio_wait(vpo, VP0_FAST_SPINTMO) != (char)0xe0) {
			*ret = VP0_ECMD_TIMEOUT;
			goto error;
		}
		if (vpoio_outstr(vpo, &command[k], 1)) {
			*ret = VP0_EPPDATA_TIMEOUT;
			goto error;
		}
	}

	/*
	 * Completion ...
	 */

	*count = 0;
	for (;;) {

		if (!(r = vpoio_wait(vpo, VP0_LOW_SPINTMO))) {
			*ret = VP0_ESTATUS_TIMEOUT;
			goto error;
		}

		/* stop when the ZIP wants to send status */
		if (r == (char)0xf0)
			break;

		if (*count >= blen) {
			*ret = VP0_EDATA_OVERFLOW;
			goto error;
		}

		/* if in EPP mode or writing bytes, try to transfer a sector
		 * otherwise, just send one byte
		 */
		if (PPB_IN_EPP_MODE(ppbus) || r == (char)0xc0)
			len = (((blen - *count) >= VP0_SECTOR_SIZE)) ?
				VP0_SECTOR_SIZE : 1;
		else
			len = 1;

		/* ZIP wants to send data? */
		if (r == (char)0xc0)
			error = vpoio_outstr(vpo, &buffer[*count], len);
		else
			error = vpoio_instr(vpo, &buffer[*count], len);

		if (error) {
			*ret = error;
			goto error;
		}

		*count += len;
	}

	if (vpoio_instr(vpo, &l, 1)) {
		*ret = VP0_EOTHER;
		goto error;
	}

	/* check if the ZIP wants to send more status */
	if (vpoio_wait(vpo, VP0_FAST_SPINTMO) == (char)0xf0)
		if (vpoio_instr(vpo, &h, 1)) {
			*ret = VP0_EOTHER + 2;
			goto error;
		}

	*result = ((int) h << 8) | ((int) l & 0xff);

error:
	/* return to printer state, release the ppbus */
	vpoio_disconnect(vpo);
	return (0);
}