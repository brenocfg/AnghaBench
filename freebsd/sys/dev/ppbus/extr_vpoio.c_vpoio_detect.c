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
struct vpoio_data {int /*<<< orphan*/  vpo_dev; int /*<<< orphan*/  vpo_mode_found; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPB_DONTWAIT ; 
 int /*<<< orphan*/  PPB_EPP ; 
 int /*<<< orphan*/  PPB_NIBBLE ; 
 int /*<<< orphan*/  PPB_PS2 ; 
 int VP0_EINITFAILED ; 
 int /*<<< orphan*/  VP0_MODE_EPP ; 
 int /*<<< orphan*/  VP0_MODE_NIBBLE ; 
 int /*<<< orphan*/  VP0_MODE_PS2 ; 
 int /*<<< orphan*/  VP0_MODE_UNDEFINED ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  connect_epp_microseq ; 
 int /*<<< orphan*/  connect_spp_microseq ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disconnect_microseq ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vpoio_in_disk_mode (struct vpoio_data*) ; 
 int /*<<< orphan*/  vpoio_reset (struct vpoio_data*) ; 

__attribute__((used)) static int
vpoio_detect(struct vpoio_data *vpo)
{
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	int error, ret;

	/* allocate the bus, then apply microsequences */
	if ((error = ppb_request_bus(ppbus, vpo->vpo_dev, PPB_DONTWAIT)))
		return (error);

	/* Force disconnection */
	ppb_MS_microseq(ppbus, vpo->vpo_dev, disconnect_microseq, &ret);

	/* Try to enter EPP mode, then connect to the drive in EPP mode */
	if (ppb_set_mode(ppbus, PPB_EPP) != -1) {
		/* call manually the microseq instead of using the appropriate function
		 * since we already requested the ppbus */
		ppb_MS_microseq(ppbus, vpo->vpo_dev, connect_epp_microseq, &ret);
	}

	/* If EPP mode switch failed or ZIP connection in EPP mode failed,
	 * try to connect in NIBBLE mode */
	if (!vpoio_in_disk_mode(vpo)) {

		/* The interface must be at least PS/2 or NIBBLE capable.
		 * There is no way to know if the ZIP will work with
		 * PS/2 mode since PS/2 and SPP both use the same connect
		 * sequence. One must suppress PS/2 with boot flags if
		 * PS/2 mode fails (see ppc(4)).
		 */
		if (ppb_set_mode(ppbus, PPB_PS2) != -1) {
			vpo->vpo_mode_found = VP0_MODE_PS2;
		} else {
			if (ppb_set_mode(ppbus, PPB_NIBBLE) == -1)
				goto error;

			vpo->vpo_mode_found = VP0_MODE_NIBBLE;
		}

		/* Can't know if the interface is capable of PS/2 yet */
		ppb_MS_microseq(ppbus, vpo->vpo_dev, connect_spp_microseq, &ret);
		if (!vpoio_in_disk_mode(vpo)) {
			vpo->vpo_mode_found = VP0_MODE_UNDEFINED;
			if (bootverbose)
				device_printf(vpo->vpo_dev,
				    "can't connect to the drive\n");

			/* disconnect and release the bus */
			ppb_MS_microseq(ppbus, vpo->vpo_dev, disconnect_microseq,
					&ret);
			goto error;
		}
	} else {
		vpo->vpo_mode_found = VP0_MODE_EPP;
	}

	/* send SCSI reset signal */
	vpoio_reset(vpo);

	ppb_MS_microseq(ppbus, vpo->vpo_dev, disconnect_microseq, &ret);

	/* ensure we are disconnected or daisy chained peripheral
	 * may cause serious problem to the disk */
	if (vpoio_in_disk_mode(vpo)) {
		if (bootverbose)
			device_printf(vpo->vpo_dev,
			    "can't disconnect from the drive\n");
		goto error;
	}

	ppb_release_bus(ppbus, vpo->vpo_dev);
	return (0);

error:
	ppb_release_bus(ppbus, vpo->vpo_dev);
	return (VP0_EINITFAILED);
}