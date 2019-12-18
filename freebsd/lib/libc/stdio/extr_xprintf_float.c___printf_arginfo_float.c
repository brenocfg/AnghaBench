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
struct printf_info {scalar_t__ is_long_double; } ;

/* Variables and functions */
 int PA_DOUBLE ; 
 int PA_FLAG_LONG_DOUBLE ; 
 int /*<<< orphan*/  assert (int) ; 

int
__printf_arginfo_float(const struct printf_info *pi, size_t n, int *argt)
{
	assert (n > 0);
	argt[0] = PA_DOUBLE;
	if (pi->is_long_double)
		argt[0] |= PA_FLAG_LONG_DOUBLE;
	return (1);
}