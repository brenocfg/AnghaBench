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

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LIST_LOCK_DESTROY () ; 
 int /*<<< orphan*/  AUDIT_PIPE_LIST_LOCK_INIT () ; 
 int /*<<< orphan*/  AUDIT_PIPE_NAME ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  audit_pipe_cdevsw ; 
 int /*<<< orphan*/ * audit_pipe_dev ; 
 int /*<<< orphan*/  audit_pipe_list ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
audit_pipe_init(void *unused)
{

	TAILQ_INIT(&audit_pipe_list);
	AUDIT_PIPE_LIST_LOCK_INIT();
	audit_pipe_dev = make_dev(&audit_pipe_cdevsw, 0, UID_ROOT,
		GID_WHEEL, 0600, "%s", AUDIT_PIPE_NAME);
	if (audit_pipe_dev == NULL) {
		AUDIT_PIPE_LIST_LOCK_DESTROY();
		panic("Can't initialize audit pipe subsystem");
	}
}