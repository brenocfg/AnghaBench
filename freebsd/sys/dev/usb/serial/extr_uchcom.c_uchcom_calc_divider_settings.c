#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {size_t dv_div; int /*<<< orphan*/  dv_prescaler; } ;
struct uchcom_divider_record {int dvr_high; int dvr_low; int dvr_base_clock; TYPE_1__ dvr_divider; } ;
struct uchcom_divider {size_t dv_div; int dv_mod; int /*<<< orphan*/  dv_prescaler; } ;

/* Variables and functions */
 size_t NUM_DIVIDERS ; 
 int UCHCOM_BASE_UNKNOWN ; 
 int UCHCOM_BPS_MOD_BASE ; 
 int UCHCOM_BPS_MOD_BASE_OFS ; 
 struct uchcom_divider_record* dividers ; 

__attribute__((used)) static int
uchcom_calc_divider_settings(struct uchcom_divider *dp, uint32_t rate)
{
	const struct uchcom_divider_record *rp;
	uint32_t div;
	uint32_t rem;
	uint32_t mod;
	uint8_t i;

	/* find record */
	for (i = 0; i != NUM_DIVIDERS; i++) {
		if (dividers[i].dvr_high >= rate &&
		    dividers[i].dvr_low <= rate) {
			rp = &dividers[i];
			goto found;
		}
	}
	return (-1);

found:
	dp->dv_prescaler = rp->dvr_divider.dv_prescaler;
	if (rp->dvr_base_clock == UCHCOM_BASE_UNKNOWN)
		dp->dv_div = rp->dvr_divider.dv_div;
	else {
		div = rp->dvr_base_clock / rate;
		rem = rp->dvr_base_clock % rate;
		if (div == 0 || div >= 0xFF)
			return (-1);
		if ((rem << 1) >= rate)
			div += 1;
		dp->dv_div = (uint8_t)-div;
	}

	mod = (UCHCOM_BPS_MOD_BASE / rate) + UCHCOM_BPS_MOD_BASE_OFS;
	mod = mod + (mod / 2);

	dp->dv_mod = (mod + 0xFF) / 0x100;

	return (0);
}