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
typedef  int time_t ;
struct module_env {scalar_t__* now; int /*<<< orphan*/  rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  autr_permit_small_holddown ; 
 scalar_t__ ub_random_max (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static time_t
calc_next_probe(struct module_env* env, time_t wait)
{
	/* make it random, 90-100% */
	time_t rnd, rest;
	if(!autr_permit_small_holddown) {
		if(wait < 3600)
			wait = 3600;
	} else {
		if(wait == 0) wait = 1;
	}
	rnd = wait/10;
	rest = wait-rnd;
	rnd = (time_t)ub_random_max(env->rnd, (long int)rnd);
	return (time_t)(*env->now + rest + rnd);
}