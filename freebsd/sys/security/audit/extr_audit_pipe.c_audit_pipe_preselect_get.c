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
struct audit_pipe_preselect {int /*<<< orphan*/  app_mask; } ;
struct audit_pipe {int dummy; } ;
typedef  int /*<<< orphan*/  au_mask_t ;
typedef  int /*<<< orphan*/  au_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int ENOENT ; 
 struct audit_pipe_preselect* audit_pipe_preselect_find (struct audit_pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
audit_pipe_preselect_get(struct audit_pipe *ap, au_id_t auid,
    au_mask_t *maskp)
{
	struct audit_pipe_preselect *app;
	int error;

	AUDIT_PIPE_LOCK(ap);
	app = audit_pipe_preselect_find(ap, auid);
	if (app != NULL) {
		*maskp = app->app_mask;
		error = 0;
	} else
		error = ENOENT;
	AUDIT_PIPE_UNLOCK(ap);
	return (error);
}