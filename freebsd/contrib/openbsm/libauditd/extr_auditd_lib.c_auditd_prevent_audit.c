#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ai_asid; } ;
typedef  TYPE_1__ auditinfo_t ;
typedef  int /*<<< orphan*/  ai ;

/* Variables and functions */
 int ADE_NOERR ; 
 int ADE_SETAUDIT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ setaudit (TYPE_1__*) ; 

int
auditd_prevent_audit(void)
{
	auditinfo_t ai;

	/*
	 * To prevent event feedback cycles and avoid audit becoming stalled if
	 * auditing is suspended we mask this processes events from being
	 * audited.  We allow the uid, tid, and mask fields to be implicitly
	 * set to zero, but do set the audit session ID to the PID.
	 *
	 * XXXRW: Is there more to it than this?
	 */
	bzero(&ai, sizeof(ai));
	ai.ai_asid = getpid();
	if (setaudit(&ai) != 0)
		return (ADE_SETAUDIT);
	return (ADE_NOERR);
}