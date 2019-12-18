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
typedef  union ieee754dp {int dummy; } ieee754dp ;

/* Variables and functions */
 scalar_t__ DPBEXP (union ieee754dp) ; 
 scalar_t__ DP_EBIAS ; 
 scalar_t__ DP_EMAX ; 

__attribute__((used)) static inline int ieee754dp_finite(union ieee754dp x)
{
	return DPBEXP(x) != DP_EMAX + 1 + DP_EBIAS;
}