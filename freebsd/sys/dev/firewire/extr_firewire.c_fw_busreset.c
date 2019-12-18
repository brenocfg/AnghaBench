#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct firewire_dev_comm {int /*<<< orphan*/  (* post_busreset ) (struct firewire_dev_comm*) ;} ;
struct firewire_comm {scalar_t__ status; int /*<<< orphan*/  config_rom; TYPE_1__* crom_src_buf; int /*<<< orphan*/  bdev; int /*<<< orphan*/  bmr_callout; } ;
struct TYPE_4__ {scalar_t__ generation; } ;
struct crom_src {TYPE_2__ businfo; } ;
typedef  scalar_t__ device_t ;
struct TYPE_3__ {struct crom_src src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROMSIZE ; 
 scalar_t__ DS_ATTACHED ; 
 scalar_t__ FWBUSMGRELECT ; 
 scalar_t__ FWBUSNOTREADY ; 
 scalar_t__ FW_GENERATION_CHANGEABLE ; 
 int /*<<< orphan*/  FW_GLOCK_ASSERT (struct firewire_comm*) ; 
 int /*<<< orphan*/  M_FW ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 scalar_t__ bcmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crom_load (struct crom_src*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,scalar_t__**,int*) ; 
 struct firewire_dev_comm* device_get_softc (scalar_t__) ; 
 scalar_t__ device_get_state (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_init_crom (struct firewire_comm*) ; 
 int /*<<< orphan*/  fw_reset_crom (struct firewire_comm*) ; 
 int /*<<< orphan*/  fw_reset_csr (struct firewire_comm*) ; 
 scalar_t__* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct firewire_dev_comm*) ; 

void
fw_busreset(struct firewire_comm *fc, uint32_t new_status)
{
	struct firewire_dev_comm *fdc;
	struct crom_src *src;
	device_t *devlistp;
	uint32_t *newrom;
	int i, devcnt;

	FW_GLOCK_ASSERT(fc);
	if (fc->status == FWBUSMGRELECT)
		callout_stop(&fc->bmr_callout);

	fc->status = new_status;
	fw_reset_csr(fc);

	if (fc->status == FWBUSNOTREADY)
		fw_init_crom(fc);

	fw_reset_crom(fc);

	if (device_get_children(fc->bdev, &devlistp, &devcnt) == 0) {
		for (i = 0; i < devcnt; i++)
			if (device_get_state(devlistp[i]) >= DS_ATTACHED) {
				fdc = device_get_softc(devlistp[i]);
				if (fdc->post_busreset != NULL)
					fdc->post_busreset(fdc);
			}
		free(devlistp, M_TEMP);
	}

	src = &fc->crom_src_buf->src;
	/*
	 * If the old config rom needs to be overwritten,
	 * bump the businfo.generation indicator to
	 * indicate that we need to be reprobed
	 * See 1394a-2000 8.3.2.5.4 for more details.
	 * generation starts at 2 and rolls over at 0xF
	 * back to 2.
	 *
	 * A generation of 0 indicates a device
	 * that is not 1394a-2000 compliant.
	 * A generation of 1 indicates a device that
	 * does not change it's Bus Info Block or
	 * Configuration ROM.
	 */
#define FW_MAX_GENERATION 0xF
	newrom = malloc(CROMSIZE, M_FW, M_NOWAIT | M_ZERO);
	src = &fc->crom_src_buf->src;
	crom_load(src, newrom, CROMSIZE);
	if (bcmp(newrom, fc->config_rom, CROMSIZE) != 0) {
		/* Bump generation and reload. */
		src->businfo.generation++;

		/* Handle generation count wraps. */
		if (src->businfo.generation < FW_GENERATION_CHANGEABLE)
			src->businfo.generation = FW_GENERATION_CHANGEABLE;

		/* Recalculate CRC to account for generation change. */
		crom_load(src, newrom, CROMSIZE);
		bcopy(newrom, fc->config_rom, CROMSIZE);
	}
	free(newrom, M_FW);
}