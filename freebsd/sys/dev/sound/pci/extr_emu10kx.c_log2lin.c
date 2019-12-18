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
 int L2L_POINTS ; 
 int* l2l_df ; 
 int* l2l_f ; 

__attribute__((used)) static int
log2lin(int log_t)
{
	int lin_t;
	int idx, lin;

	if (log_t <= 0) {
		lin_t = 0x00000000;
		return (lin_t);
	}

	if (log_t >= 100) {
		lin_t = 0x7fffffff;
		return (lin_t);
	}

	idx = (L2L_POINTS - 1) - log_t / (L2L_POINTS);
	lin = log_t % (L2L_POINTS);
	lin_t = l2l_df[idx] * lin + l2l_f[idx];
	return (lin_t);
}