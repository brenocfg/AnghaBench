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
struct torus {int /*<<< orphan*/ * sw_pool; scalar_t__ switch_cnt; } ;

/* Variables and functions */
 scalar_t__ torus_lft (struct torus*,int /*<<< orphan*/ ) ; 
 scalar_t__ torus_master_stree (struct torus*) ; 

int route_torus(struct torus *t)
{
	int s;
	bool success = true;

	for (s = 0; s < (int)t->switch_cnt; s++)
		success = torus_lft(t, t->sw_pool[s]) && success;

	success = success && torus_master_stree(t);

	return success ? 0 : -1;
}