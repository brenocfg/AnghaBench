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
struct audit_pipe_preselect {int dummy; } ;
struct audit_pipe {int /*<<< orphan*/  ap_preselect_list; } ;
typedef  int /*<<< orphan*/  au_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  M_AUDIT_PIPE_PRESELECT ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct audit_pipe_preselect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_list ; 
 struct audit_pipe_preselect* audit_pipe_preselect_find (struct audit_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct audit_pipe_preselect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
audit_pipe_preselect_delete(struct audit_pipe *ap, au_id_t auid)
{
	struct audit_pipe_preselect *app;
	int error;

	AUDIT_PIPE_LOCK(ap);
	app = audit_pipe_preselect_find(ap, auid);
	if (app != NULL) {
		TAILQ_REMOVE(&ap->ap_preselect_list, app, app_list);
		error = 0;
	} else
		error = ENOENT;
	AUDIT_PIPE_UNLOCK(ap);
	if (app != NULL)
		free(app, M_AUDIT_PIPE_PRESELECT);
	return (error);
}