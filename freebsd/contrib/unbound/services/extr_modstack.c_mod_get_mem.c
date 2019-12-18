#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module_env {TYPE_1__* mesh; } ;
struct TYPE_6__ {TYPE_2__** mod; } ;
struct TYPE_5__ {size_t (* get_mem ) (struct module_env*,int) ;} ;
struct TYPE_4__ {TYPE_3__ mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mod_get_mem (size_t (*) (struct module_env*,int)) ; 
 int modstack_find (TYPE_3__*,char const*) ; 
 size_t stub1 (struct module_env*,int) ; 

size_t
mod_get_mem(struct module_env* env, const char* name)
{
	int m = modstack_find(&env->mesh->mods, name);
	if(m != -1) {
		fptr_ok(fptr_whitelist_mod_get_mem(env->mesh->
			mods.mod[m]->get_mem));
		return (*env->mesh->mods.mod[m]->get_mem)(env, m);
	}
	return 0;
}