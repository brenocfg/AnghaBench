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
struct module_env {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (struct module_env*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mod_deinit (int /*<<< orphan*/  (*) (struct module_env*,int)) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  stub1 (struct module_env*,int) ; 

void 
modstack_desetup(struct module_stack* stack, struct module_env* env)
{
        int i;
        for(i=0; i<stack->num; i++) {
                fptr_ok(fptr_whitelist_mod_deinit(stack->mod[i]->deinit));
                (*stack->mod[i]->deinit)(env, i);
        }
        stack->num = 0;
        free(stack->mod);
        stack->mod = NULL;
}