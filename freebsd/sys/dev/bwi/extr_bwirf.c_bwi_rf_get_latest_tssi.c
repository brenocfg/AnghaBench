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
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_HI_TSSI_MASK ; 
 scalar_t__ BWI_INVALID_TSSI ; 
 int /*<<< orphan*/  BWI_LO_TSSI_MASK ; 
 int EINVAL ; 
 scalar_t__ MOBJ_READ_2 (struct bwi_mac*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ __SHIFTOUT (scalar_t__,int /*<<< orphan*/ ) ; 

int
bwi_rf_get_latest_tssi(struct bwi_mac *mac, int8_t tssi[], uint16_t ofs)
{
	int i;

	for (i = 0; i < 4; ) {
		uint16_t val;

		val = MOBJ_READ_2(mac, BWI_COMM_MOBJ, ofs + i);
		tssi[i++] = (int8_t)__SHIFTOUT(val, BWI_LO_TSSI_MASK);
		tssi[i++] = (int8_t)__SHIFTOUT(val, BWI_HI_TSSI_MASK);
	}

	for (i = 0; i < 4; ++i) {
		if (tssi[i] == BWI_INVALID_TSSI)
			return EINVAL;
	}
	return 0;
}