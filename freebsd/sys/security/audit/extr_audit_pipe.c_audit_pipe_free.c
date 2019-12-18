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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct audit_pipe {TYPE_1__ ap_selinfo; int /*<<< orphan*/  ap_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LIST_WLOCK_ASSERT () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_DESTROY (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_SX_LOCK_DESTROY (struct audit_pipe*) ; 
 int /*<<< orphan*/  M_AUDIT_PIPE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct audit_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_list ; 
 int /*<<< orphan*/  audit_pipe_count ; 
 int /*<<< orphan*/  audit_pipe_flush (struct audit_pipe*) ; 
 int /*<<< orphan*/  audit_pipe_list ; 
 int /*<<< orphan*/  audit_pipe_preselect_flush_locked (struct audit_pipe*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct audit_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
audit_pipe_free(struct audit_pipe *ap)
{

	AUDIT_PIPE_LIST_WLOCK_ASSERT();
	AUDIT_PIPE_LOCK_ASSERT(ap);

	audit_pipe_preselect_flush_locked(ap);
	audit_pipe_flush(ap);
	cv_destroy(&ap->ap_cv);
	AUDIT_PIPE_SX_LOCK_DESTROY(ap);
	AUDIT_PIPE_LOCK_DESTROY(ap);
	seldrain(&ap->ap_selinfo);
	knlist_destroy(&ap->ap_selinfo.si_note);
	TAILQ_REMOVE(&audit_pipe_list, ap, ap_list);
	free(ap, M_AUDIT_PIPE);
	audit_pipe_count--;
}