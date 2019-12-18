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
typedef  int u64 ;
struct n2rng {TYPE_1__* data; } ;
struct TYPE_2__ {int chip_version; } ;

/* Variables and functions */
 int N2RNG_ACCUM_CYCLES_DEFAULT ; 
 int RNG_CTL_ES1 ; 
 int RNG_CTL_ES2 ; 
 int RNG_CTL_ES3 ; 
 int RNG_CTL_LFSR ; 
 int RNG_v1_CTL_ASEL_SHIFT ; 
 int RNG_v1_CTL_VCO_SHIFT ; 
 int RNG_v1_CTL_WAIT_SHIFT ; 
 int RNG_v2_CTL_ASEL_SHIFT ; 
 int RNG_v2_CTL_VCO_SHIFT ; 
 int RNG_v2_CTL_WAIT_SHIFT ; 

__attribute__((used)) static u64 n2rng_control_default(struct n2rng *np, int ctl)
{
	u64 val = 0;

	if (np->data->chip_version == 1) {
		val = ((2 << RNG_v1_CTL_ASEL_SHIFT) |
			(N2RNG_ACCUM_CYCLES_DEFAULT << RNG_v1_CTL_WAIT_SHIFT) |
			 RNG_CTL_LFSR);

		switch (ctl) {
		case 0:
			val |= (1 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES1;
			break;
		case 1:
			val |= (2 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES2;
			break;
		case 2:
			val |= (3 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES3;
			break;
		case 3:
			val |= RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3;
			break;
		default:
			break;
		}

	} else {
		val = ((2 << RNG_v2_CTL_ASEL_SHIFT) |
			(N2RNG_ACCUM_CYCLES_DEFAULT << RNG_v2_CTL_WAIT_SHIFT) |
			 RNG_CTL_LFSR);

		switch (ctl) {
		case 0:
			val |= (1 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES1;
			break;
		case 1:
			val |= (2 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES2;
			break;
		case 2:
			val |= (3 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES3;
			break;
		case 3:
			val |= RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3;
			break;
		default:
			break;
		}
	}

	return val;
}