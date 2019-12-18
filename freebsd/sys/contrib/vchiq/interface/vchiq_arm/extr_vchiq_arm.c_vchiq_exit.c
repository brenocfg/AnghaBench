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

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_state ; 
 int /*<<< orphan*/ * vchiq_cdev ; 
 int /*<<< orphan*/  vchiq_platform_exit (int /*<<< orphan*/ *) ; 

void
vchiq_exit(void)
{

	vchiq_platform_exit(&g_state);
	if (vchiq_cdev) {
		destroy_dev(vchiq_cdev);
		vchiq_cdev = NULL;
	}
}