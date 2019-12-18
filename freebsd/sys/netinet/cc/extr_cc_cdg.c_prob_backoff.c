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

/* Variables and functions */
 long D_P_E ; 
 int EXP_PREC ; 
 int INT_MAX ; 
 long MAXGRAD ; 
 long V_cdg_exp_backoff_scale ; 
 int* probexp ; 
 int random () ; 

__attribute__((used)) static inline int
prob_backoff(long qtrend)
{
	int backoff, idx, p;

	backoff = (qtrend > ((MAXGRAD * V_cdg_exp_backoff_scale) << D_P_E));

	if (!backoff) {
		if (V_cdg_exp_backoff_scale > 1)
			idx = (qtrend + V_cdg_exp_backoff_scale / 2) /
			    V_cdg_exp_backoff_scale;
		else
			idx = qtrend;

		/* Backoff probability proportional to rate of queue growth. */
		p = (INT_MAX / (1 << EXP_PREC)) * probexp[idx];
		backoff = (random() < p);
	}

	return (backoff);
}