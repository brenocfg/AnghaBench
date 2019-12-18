#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * syminfo; } ;
struct module {scalar_t__ state; TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ MODULE_STATE_LIVE ; 
 scalar_t__ is_livepatch_module (struct module*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void module_arch_freeing_init(struct module *mod)
{
	if (is_livepatch_module(mod) &&
	    mod->state == MODULE_STATE_LIVE)
		return;

	vfree(mod->arch.syminfo);
	mod->arch.syminfo = NULL;
}