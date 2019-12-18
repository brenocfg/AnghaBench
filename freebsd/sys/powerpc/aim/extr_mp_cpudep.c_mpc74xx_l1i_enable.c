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
 int HID0_ICE ; 
 int HID0_ICFI ; 
 int /*<<< orphan*/  SPR_HID0 ; 
 int /*<<< orphan*/  isync () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static register_t
mpc74xx_l1i_enable(void)
{
	register_t hid;

	hid = mfspr(SPR_HID0);
	if (hid & HID0_ICE)
		return (hid);

	/* Enable L1 I-cache */
	hid |= HID0_ICE;
	isync();
	mtspr(SPR_HID0, hid | HID0_ICFI);
	isync();

	return (hid);
}