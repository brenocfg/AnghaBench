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
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 

__attribute__((used)) static void
bwi_rf_off_11g_rev5(struct bwi_mac *mac)
{
	PHY_SETBITS(mac, 0x811, 0x8c);
	PHY_CLRBITS(mac, 0x812, 0x8c);
}