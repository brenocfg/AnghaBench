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
struct env {int /*<<< orphan*/ * sc_group_names_t; int /*<<< orphan*/ * sc_user_names_t; scalar_t__ sc_group_line_len; scalar_t__ sc_user_line_len; scalar_t__ update_trashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

void
main_start_update(struct env *env)
{
	env->update_trashed = 0;

	log_debug("starting directory update");
	env->sc_user_line_len = 0;
	env->sc_group_line_len = 0;
	if ((env->sc_user_names_t = calloc(1,
	    sizeof(*env->sc_user_names_t))) == NULL ||
	    (env->sc_group_names_t = calloc(1,
	    sizeof(*env->sc_group_names_t))) == NULL)
		fatal(NULL);
	RB_INIT(env->sc_user_names_t);
	RB_INIT(env->sc_group_names_t);
}