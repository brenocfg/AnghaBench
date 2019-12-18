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
struct nitrox_q_vector {struct nitrox_device* ndev; } ;
struct nitrox_device {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ __NDEV_MODE_PF ; 

__attribute__((used)) static void nps_core_int_tasklet(unsigned long data)
{
	struct nitrox_q_vector *qvec = (void *)(uintptr_t)(data);
	struct nitrox_device *ndev = qvec->ndev;

	/* if pf mode do queue recovery */
	if (ndev->mode == __NDEV_MODE_PF) {
	} else {
		/**
		 * if VF(s) enabled communicate the error information
		 * to VF(s)
		 */
	}
}