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
 int PPB_WAIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_connect (struct vpoio_data*,int,int*,int) ; 
 int /*<<< orphan*/  imm_disconnect (struct vpoio_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_microseq ; 

int
imm_reset_bus(struct vpoio_data *vpo)
{
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	int disconnected;

	/* first, connect to the drive and request the bus */
	imm_connect(vpo, PPB_WAIT|PPB_INTR, &disconnected, 1);

	if (!disconnected) {

		/* reset the SCSI bus */
		ppb_MS_microseq(ppbus, vpo->vpo_dev, reset_microseq, NULL);

		/* then disconnect */
		imm_disconnect(vpo, NULL, 1);
	}

	return (0);
}