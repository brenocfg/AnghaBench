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
struct audit_pipe {int /*<<< orphan*/  ap_preselect_mode; int /*<<< orphan*/  ap_preselect_list; int /*<<< orphan*/  ap_preselect_naflags; int /*<<< orphan*/  ap_preselect_flags; int /*<<< orphan*/  ap_cv; TYPE_1__ ap_selinfo; int /*<<< orphan*/  ap_queue; int /*<<< orphan*/  ap_qlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDITPIPE_PRESELECT_MODE_TRAIL ; 
 int /*<<< orphan*/  AUDIT_PIPE_LIST_WLOCK () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LIST_WUNLOCK () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_INIT (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_MTX (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_QLIMIT_DEFAULT ; 
 int /*<<< orphan*/  AUDIT_PIPE_SX_LOCK_INIT (struct audit_pipe*) ; 
 int /*<<< orphan*/  M_AUDIT_PIPE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct audit_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_list ; 
 int /*<<< orphan*/  audit_pipe_count ; 
 int /*<<< orphan*/  audit_pipe_ever ; 
 int /*<<< orphan*/  audit_pipe_list ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct audit_pipe* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct audit_pipe *
audit_pipe_alloc(void)
{
	struct audit_pipe *ap;

	ap = malloc(sizeof(*ap), M_AUDIT_PIPE, M_NOWAIT | M_ZERO);
	if (ap == NULL)
		return (NULL);
	ap->ap_qlimit = AUDIT_PIPE_QLIMIT_DEFAULT;
	TAILQ_INIT(&ap->ap_queue);
	knlist_init_mtx(&ap->ap_selinfo.si_note, AUDIT_PIPE_MTX(ap));
	AUDIT_PIPE_LOCK_INIT(ap);
	AUDIT_PIPE_SX_LOCK_INIT(ap);
	cv_init(&ap->ap_cv, "audit_pipe");

	/*
	 * Default flags, naflags, and auid-specific preselection settings to
	 * 0.  Initialize the mode to the global trail so that if praudit(1)
	 * is run on /dev/auditpipe, it sees events associated with the
	 * default trail.  Pipe-aware application can clear the flag, set
	 * custom masks, and flush the pipe as needed.
	 */
	bzero(&ap->ap_preselect_flags, sizeof(ap->ap_preselect_flags));
	bzero(&ap->ap_preselect_naflags, sizeof(ap->ap_preselect_naflags));
	TAILQ_INIT(&ap->ap_preselect_list);
	ap->ap_preselect_mode = AUDITPIPE_PRESELECT_MODE_TRAIL;

	/*
	 * Add to global list and update global statistics.
	 */
	AUDIT_PIPE_LIST_WLOCK();
	TAILQ_INSERT_HEAD(&audit_pipe_list, ap, ap_list);
	audit_pipe_count++;
	audit_pipe_ever++;
	AUDIT_PIPE_LIST_WUNLOCK();

	return (ap);
}