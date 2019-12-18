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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 

__attribute__((used)) static int
bwi_rf_gain_max_reached(struct bwi_mac *mac, int idx)
{
	PHY_FILT_SETBITS(mac, 0x812, 0xf0ff, idx << 8);
	PHY_FILT_SETBITS(mac, 0x15, 0xfff, 0xa000);
	PHY_SETBITS(mac, 0x15, 0xf000);

	DELAY(20);

	return (PHY_READ(mac, 0x2d) >= 0xdfc);
}