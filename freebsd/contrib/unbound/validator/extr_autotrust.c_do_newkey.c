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
struct module_env {int dummy; } ;
struct autr_ta {scalar_t__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTR_STATE_ADDPEND ; 
 scalar_t__ AUTR_STATE_START ; 
 int /*<<< orphan*/  set_trustanchor_state (struct module_env*,struct autr_ta*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_newkey(struct module_env* env, struct autr_ta* anchor, int* c)
{
	if (anchor->s == AUTR_STATE_START)
		set_trustanchor_state(env, anchor, c, AUTR_STATE_ADDPEND);
}