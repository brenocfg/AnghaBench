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

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 
 int /*<<< orphan*/  M_AUDIT_PIPE_PRESELECT ; 
 struct audit_pipe_preselect* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct audit_pipe_preselect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_list ; 
 int /*<<< orphan*/  free (struct audit_pipe_preselect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_pipe_preselect_flush_locked(struct audit_pipe *ap)
{
	struct audit_pipe_preselect *app;

	AUDIT_PIPE_LOCK_ASSERT(ap);

	while ((app = TAILQ_FIRST(&ap->ap_preselect_list)) != NULL) {
		TAILQ_REMOVE(&ap->ap_preselect_list, app, app_list);
		free(app, M_AUDIT_PIPE_PRESELECT);
	}
}