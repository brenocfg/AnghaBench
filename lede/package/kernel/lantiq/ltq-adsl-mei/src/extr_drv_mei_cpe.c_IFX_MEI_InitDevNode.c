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
 int ENODEV ; 
 int /*<<< orphan*/  IFX_MEI_DEVNAME ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsp_mei_operations ; 
 int /*<<< orphan*/  dev_major ; 
 int /*<<< orphan*/  register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
IFX_MEI_InitDevNode (int num)
{
	if (num == 0) {
		if ((dev_major = register_chrdev (dev_major, IFX_MEI_DEVNAME, &bsp_mei_operations)) < 0) {
			IFX_MEI_EMSG ("register_chrdev(%d %s) failed!\n", dev_major, IFX_MEI_DEVNAME);
			return -ENODEV;
		}
	}
	return 0;
}