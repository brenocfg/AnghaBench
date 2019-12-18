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
struct ck_barrier_combining_state {int /*<<< orphan*/  sense; } ;
struct ck_barrier_combining_group {int dummy; } ;
struct ck_barrier_combining {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_barrier_combining_aux (struct ck_barrier_combining*,struct ck_barrier_combining_group*,int /*<<< orphan*/ ) ; 

void
ck_barrier_combining(struct ck_barrier_combining *barrier,
    struct ck_barrier_combining_group *tnode,
    struct ck_barrier_combining_state *state)
{

	ck_barrier_combining_aux(barrier, tnode, state->sense);

	/* Reverse the execution context's sense for the next barrier. */
	state->sense = ~state->sense;
	return;
}