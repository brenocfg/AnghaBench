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
struct module_stack {int num; TYPE_1__** mod; } ;
struct module_env {scalar_t__ need_to_validate; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  (* init ) (struct module_env*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mod_init (int /*<<< orphan*/  (*) (struct module_env*,int)) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modstack_config (struct module_stack*,char const*) ; 
 int /*<<< orphan*/  modstack_desetup (struct module_stack*,struct module_env*) ; 
 int /*<<< orphan*/  stub1 (struct module_env*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int 
modstack_setup(struct module_stack* stack, const char* module_conf,
	struct module_env* env)
{
        int i;
        if(stack->num != 0)
                modstack_desetup(stack, env);
        /* fixed setup of the modules */
        if(!modstack_config(stack, module_conf)) {
		return 0;
        }
        env->need_to_validate = 0; /* set by module init below */
        for(i=0; i<stack->num; i++) {
                verbose(VERB_OPS, "init module %d: %s",
                        i, stack->mod[i]->name);
                fptr_ok(fptr_whitelist_mod_init(stack->mod[i]->init));
                if(!(*stack->mod[i]->init)(env, i)) {
                        log_err("module init for module %s failed",
                                stack->mod[i]->name);
			return 0;
                }
        }
	return 1;
}