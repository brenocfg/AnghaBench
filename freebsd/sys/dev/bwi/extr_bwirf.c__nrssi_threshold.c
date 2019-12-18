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
struct bwi_rf {int* rf_nrssi; } ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static __inline int32_t
_nrssi_threshold(const struct bwi_rf *rf, int32_t val)
{
	val *= (rf->rf_nrssi[1] - rf->rf_nrssi[0]);
	val += (rf->rf_nrssi[0] << 6);
	if (val < 32)
		val += 31;
	else
		val += 32;
	val >>= 6;
	if (val < -31)
		val = -31;
	else if (val > 31)
		val = 31;
	return val;
}