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
typedef  int register_t ;

/* Variables and functions */
 int HID0_DCE ; 
 int HID0_DCFI ; 
 int /*<<< orphan*/  SPR_HID0 ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static register_t
mpc74xx_l1d_enable(void)
{
	register_t hid;

	hid = mfspr(SPR_HID0);
	if (hid & HID0_DCE)
		return (hid);

	/* Enable L1 D-cache */
	hid |= HID0_DCE;
	powerpc_sync();
	mtspr(SPR_HID0, hid | HID0_DCFI);
	powerpc_sync();

	return (hid);
}