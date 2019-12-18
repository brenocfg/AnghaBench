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
struct userent {struct userent* ge_line; struct userent* ue_netid_line; struct userent* ue_line; } ;
struct groupent {struct groupent* ge_line; struct groupent* ue_netid_line; struct groupent* ue_line; } ;
struct env {int update_trashed; struct userent* sc_group_names_t; struct userent* sc_user_names_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,struct userent*,struct userent*) ; 
 struct userent* RB_ROOT (struct userent*) ; 
 int /*<<< orphan*/  free (struct userent*) ; 
 int /*<<< orphan*/  group_name_tree ; 
 int /*<<< orphan*/  user_name_tree ; 

void
main_trash_update(struct env *env)
{
	struct userent	*ue;
	struct groupent	*ge;

	env->update_trashed = 1;

	while ((ue = RB_ROOT(env->sc_user_names_t)) != NULL) {
		RB_REMOVE(user_name_tree,
		    env->sc_user_names_t, ue);
		free(ue->ue_line);
		free(ue->ue_netid_line);
		free(ue);
	}
	free(env->sc_user_names_t);
	env->sc_user_names_t = NULL;
	while ((ge = RB_ROOT(env->sc_group_names_t))
	    != NULL) {
		RB_REMOVE(group_name_tree,
		    env->sc_group_names_t, ge);
		free(ge->ge_line);
		free(ge);
	}
	free(env->sc_group_names_t);
	env->sc_group_names_t = NULL;
}