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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int NSHUFF ; 
 scalar_t__ TYPE_0 ; 
 int /*<<< orphan*/ * fptr ; 
 int /*<<< orphan*/  good_rand (int /*<<< orphan*/ ) ; 
 int rand_deg ; 
 size_t rand_sep ; 
 scalar_t__ rand_type ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/ * rptr ; 
 int /*<<< orphan*/ * state ; 

void
srandom(unsigned int x)
{
	int i, lim;

	state[0] = (uint32_t)x;
	if (rand_type == TYPE_0)
		lim = NSHUFF;
	else {
		for (i = 1; i < rand_deg; i++)
			state[i] = good_rand(state[i - 1]);
		fptr = &state[rand_sep];
		rptr = &state[0];
		lim = 10 * rand_deg;
	}
	for (i = 0; i < lim; i++)
		(void)random();
}