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
struct cf_setting {int freq; } ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int HID1_DFS2 ; 
 int HID1_DFS4 ; 
 int /*<<< orphan*/  SPR_HID1 ; 
 int /*<<< orphan*/  isync () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static int
dfs_set(device_t dev, const struct cf_setting *set)
{
	register_t hid1;
	
	if (set == NULL)
		return (EINVAL);

	hid1 = mfspr(SPR_HID1);
	hid1 &= ~(HID1_DFS2 | HID1_DFS4);

	if (set->freq == 5000)
		hid1 |= HID1_DFS2;
	else if (set->freq == 2500)
		hid1 |= HID1_DFS4;
	
	/*
	 * Now set the HID1 register with new values. Calling sequence
	 * taken from page 2-26 of the MPC7450 family CPU manual.
	 */

	powerpc_sync();
	mtspr(SPR_HID1, hid1);
	powerpc_sync(); isync();

	return (0);
}