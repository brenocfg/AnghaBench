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
 int imm_detect (struct vpoio_data*) ; 

int
imm_probe(device_t dev, struct vpoio_data *vpo)
{
	int error;

	/* ppbus dependent initialisation */
	vpo->vpo_dev = dev;

	/* now, try to initialise the drive */
	if ((error = imm_detect(vpo))) {
		return (error);
	}

	return (0);
}