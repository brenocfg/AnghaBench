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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ TYPE_0 ; 
 int* end_ptr ; 
 int* fptr ; 
 int good_rand (int) ; 
 scalar_t__ rand_type ; 
 int* rptr ; 
 int* state ; 

long
random(void)
{
	uint32_t i;
	uint32_t *f, *r;

	if (rand_type == TYPE_0) {
		i = state[0];
		state[0] = i = good_rand(i);
	} else {
		/*
		 * Use local variables rather than static variables for speed.
		 */
		f = fptr; r = rptr;
		*f += *r;
		i = *f >> 1;	/* chucking least random bit */
		if (++f >= end_ptr) {
			f = state;
			++r;
		}
		else if (++r >= end_ptr) {
			r = state;
		}

		fptr = f; rptr = r;
	}
	return ((long)i);
}