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
struct module_func_block {int /*<<< orphan*/  (* deinit ) (struct module_env*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* init ) (struct module_env*,int /*<<< orphan*/ ) ;} ;
struct module_env {int /*<<< orphan*/  scratch; int /*<<< orphan*/  scratch_buffer; struct config_file* cfg; } ;
struct config_file {int dummy; } ;
typedef  int /*<<< orphan*/  env ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  edns_known_options_delete (struct module_env*) ; 
 int /*<<< orphan*/  edns_known_options_init (struct module_env*) ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 int /*<<< orphan*/  memset (struct module_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regional_create () ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct module_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct module_env*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_mod(struct config_file* cfg, struct module_func_block* fb)
{
	struct module_env env;
	memset(&env, 0, sizeof(env));
	env.cfg = cfg;
	env.scratch = regional_create();
	env.scratch_buffer = sldns_buffer_new(BUFSIZ);
	if(!env.scratch || !env.scratch_buffer)
		fatal_exit("out of memory");
	if(!edns_known_options_init(&env))
		fatal_exit("out of memory");
	if(!(*fb->init)(&env, 0)) {
		fatal_exit("bad config for %s module", fb->name);
	}
	(*fb->deinit)(&env, 0);
	sldns_buffer_free(env.scratch_buffer);
	regional_destroy(env.scratch);
	edns_known_options_delete(&env);
}