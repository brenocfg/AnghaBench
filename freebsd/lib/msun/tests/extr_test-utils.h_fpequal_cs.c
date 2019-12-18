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
 scalar_t__ fabsl (long double) ; 
 scalar_t__ isnan (long double) ; 
 int /*<<< orphan*/  signbit (long double) ; 

__attribute__((used)) static int
fpequal_cs(long double x, long double y, int checksign)
{
	if (isnan(x) && isnan(y))
		return (1);
	if (checksign)
		return (x == y && !signbit(x) == !signbit(y));
	else
		return (fabsl(x) == fabsl(y));
}