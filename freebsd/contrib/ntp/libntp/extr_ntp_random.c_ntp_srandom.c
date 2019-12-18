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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 scalar_t__ TYPE_0 ; 
 unsigned long* fptr ; 
 unsigned long good_rand (unsigned long) ; 
 unsigned long ntp_random () ; 
 long rand_deg ; 
 size_t rand_sep ; 
 scalar_t__ rand_type ; 
 unsigned long* rptr ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 unsigned long* state ; 

void
ntp_srandom(
	unsigned long x
	)
{
	long i;

	if (rand_type == TYPE_0) {
		state[0] = x;
	} else {
		state[0] = x;
		for (i = 1; i < rand_deg; i++)
			state[i] = good_rand(state[i - 1]);
		fptr = &state[rand_sep];
		rptr = &state[0];
		for (i = 0; i < 10 * rand_deg; i++)
			x = ntp_random();
	}

	/* seed the likely faster (and poorer) rand() as well */
	srand((u_int)x);
}