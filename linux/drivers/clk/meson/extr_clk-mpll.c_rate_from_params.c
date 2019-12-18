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
typedef  unsigned int u64 ;

/* Variables and functions */
 long DIV_ROUND_UP_ULL (unsigned int,unsigned long) ; 
 long EINVAL ; 
 unsigned int N2_MIN ; 
 unsigned int SDM_DEN ; 

__attribute__((used)) static long rate_from_params(unsigned long parent_rate,
			     unsigned int sdm,
			     unsigned int n2)
{
	unsigned long divisor = (SDM_DEN * n2) + sdm;

	if (n2 < N2_MIN)
		return -EINVAL;

	return DIV_ROUND_UP_ULL((u64)parent_rate * SDM_DEN, divisor);
}