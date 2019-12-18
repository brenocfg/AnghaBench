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
struct audit_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  audit_pipe_preselect_flush_locked (struct audit_pipe*) ; 

__attribute__((used)) static void
audit_pipe_preselect_flush(struct audit_pipe *ap)
{

	AUDIT_PIPE_LOCK(ap);
	audit_pipe_preselect_flush_locked(ap);
	AUDIT_PIPE_UNLOCK(ap);
}