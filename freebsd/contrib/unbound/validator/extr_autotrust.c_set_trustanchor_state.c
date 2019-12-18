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
struct autr_ta {int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  autr_state_type ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  reset_holddown (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  trustanchor_state2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose_key (struct autr_ta*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_trustanchor_state(struct module_env* env, struct autr_ta* ta, int* changed,
	autr_state_type s)
{
	verbose_key(ta, VERB_ALGO, "update: %s to %s",
		trustanchor_state2str(ta->s), trustanchor_state2str(s));
	ta->s = s;
	reset_holddown(env, ta, changed);
}