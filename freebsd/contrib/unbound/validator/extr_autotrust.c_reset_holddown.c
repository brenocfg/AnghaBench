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
struct module_env {int /*<<< orphan*/ * now; } ;
struct autr_ta {int /*<<< orphan*/  last_change; } ;

/* Variables and functions */

__attribute__((used)) static void
reset_holddown(struct module_env* env, struct autr_ta* ta, int* changed)
{
	ta->last_change = *env->now;
	*changed = 1;
}