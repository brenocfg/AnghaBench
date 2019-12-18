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
struct printf_info {scalar_t__ is_char; scalar_t__ is_short; scalar_t__ is_long_double; scalar_t__ is_quad; scalar_t__ is_intmax; scalar_t__ is_long; scalar_t__ is_size; scalar_t__ is_ptrdiff; } ;

/* Variables and functions */
 int PA_CHAR ; 
 int PA_FLAG_INTMAX ; 
 int PA_FLAG_LONG ; 
 int PA_FLAG_LONG_LONG ; 
 int PA_FLAG_PTRDIFF ; 
 int PA_FLAG_QUAD ; 
 int PA_FLAG_SHORT ; 
 int PA_FLAG_SIZE ; 
 int PA_INT ; 
 int /*<<< orphan*/  assert (int) ; 

int
__printf_arginfo_int(const struct printf_info *pi, size_t n, int *argt)
{
	assert (n > 0);
	argt[0] = PA_INT;
	if (pi->is_ptrdiff)
		argt[0] |= PA_FLAG_PTRDIFF;
	else if (pi->is_size)
		argt[0] |= PA_FLAG_SIZE;
	else if (pi->is_long)
		argt[0] |= PA_FLAG_LONG;
	else if (pi->is_intmax)
		argt[0] |= PA_FLAG_INTMAX;
	else if (pi->is_quad)
		argt[0] |= PA_FLAG_QUAD;
	else if (pi->is_long_double)
		argt[0] |= PA_FLAG_LONG_LONG;
	else if (pi->is_short)
		argt[0] |= PA_FLAG_SHORT;
	else if (pi->is_char)
		argt[0] = PA_CHAR;
	return (1);
}