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
typedef  int u32 ;
struct ve_spc_opp {int freq; } ;
struct TYPE_2__ {int* num_opps; struct ve_spc_opp** opps; } ;

/* Variables and functions */
 TYPE_1__* info ; 

__attribute__((used)) static int ve_spc_round_performance(int cluster, u32 freq)
{
	int idx, max_opp = info->num_opps[cluster];
	struct ve_spc_opp *opps = info->opps[cluster];
	u32 fmin = 0, fmax = ~0, ftmp;

	freq /= 1000; /* OPP entries in kHz */
	for (idx = 0; idx < max_opp; idx++, opps++) {
		ftmp = opps->freq;
		if (ftmp >= freq) {
			if (ftmp <= fmax)
				fmax = ftmp;
		} else {
			if (ftmp >= fmin)
				fmin = ftmp;
		}
	}
	if (fmax != ~0)
		return fmax * 1000;
	else
		return fmin * 1000;
}