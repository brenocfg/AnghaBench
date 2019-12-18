#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct daemon {TYPE_2__* env; TYPE_1__* cfg; int /*<<< orphan*/  mods; int /*<<< orphan*/  superalloc; } ;
struct TYPE_5__ {scalar_t__ need_to_validate; int /*<<< orphan*/ * worker; int /*<<< orphan*/ * alloc; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  module_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  log_edns_known_options (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  modstack_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void daemon_setup_modules(struct daemon* daemon)
{
	daemon->env->cfg = daemon->cfg;
	daemon->env->alloc = &daemon->superalloc;
	daemon->env->worker = NULL;
	daemon->env->need_to_validate = 0; /* set by module init below */
	if(!modstack_setup(&daemon->mods, daemon->cfg->module_conf, 
		daemon->env)) {
		fatal_exit("failed to setup modules");
	}
	log_edns_known_options(VERB_ALGO, daemon->env);
}