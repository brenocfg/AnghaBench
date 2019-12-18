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
struct knote {scalar_t__ kn_hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct audit_pipe {TYPE_1__ ap_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 

__attribute__((used)) static void
audit_pipe_kqdetach(struct knote *kn)
{
	struct audit_pipe *ap;

	ap = (struct audit_pipe *)kn->kn_hook;
	AUDIT_PIPE_LOCK(ap);
	knlist_remove(&ap->ap_selinfo.si_note, kn, 1);
	AUDIT_PIPE_UNLOCK(ap);
}