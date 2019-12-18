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
typedef  scalar_t__ uint16_t ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_RF_NOISE ; 
 scalar_t__ MOBJ_READ_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwi_rf_calc_noise_bcm2053(struct bwi_mac *mac)
{
	uint16_t val;
	int noise;

	val = MOBJ_READ_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_RF_NOISE);
	noise = (int)val;	/* XXX check bounds? */

	noise = ((noise - 11) * 103) / 64;
	noise -= 109;
	return noise;
}