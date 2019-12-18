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
struct vpo_data {int vpo_isplus; int /*<<< orphan*/  vpo_io; int /*<<< orphan*/  vpo_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct vpo_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int imm_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int vpoio_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vpo_probe(device_t dev)
{
	device_t ppbus = device_get_parent(dev);
	struct vpo_data *vpo;
	int error;

	vpo = DEVTOSOFTC(dev);
	vpo->vpo_dev = dev;

	/* check ZIP before ZIP+ or imm_probe() will send controls to
	 * the printer or whatelse connected to the port */
	ppb_lock(ppbus);
	if ((error = vpoio_probe(dev, &vpo->vpo_io)) == 0) {
		vpo->vpo_isplus = 0;
		device_set_desc(dev,
				"Iomega VPI0 Parallel to SCSI interface");
	} else if ((error = imm_probe(dev, &vpo->vpo_io)) == 0) {
		vpo->vpo_isplus = 1;
		device_set_desc(dev,
				"Iomega Matchmaker Parallel to SCSI interface");
	} else {
		ppb_unlock(ppbus);
		return (error);
	}
	ppb_unlock(ppbus);

	return (0);
}