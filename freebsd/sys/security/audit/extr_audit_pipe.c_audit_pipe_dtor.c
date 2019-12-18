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
struct audit_pipe {int /*<<< orphan*/  ap_sigio; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LIST_WLOCK () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LIST_WUNLOCK () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  audit_pipe_free (struct audit_pipe*) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audit_pipe_dtor(void *arg)
{
	struct audit_pipe *ap;

	ap = arg;
	funsetown(&ap->ap_sigio);
	AUDIT_PIPE_LIST_WLOCK();
	AUDIT_PIPE_LOCK(ap);
	audit_pipe_free(ap);
	AUDIT_PIPE_LIST_WUNLOCK();
}