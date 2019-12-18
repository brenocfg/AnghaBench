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
struct procinfo {struct conninfo* pr_conn; } ;
struct conninfo {int co_numchild; struct procinfo** co_proc; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_conn (struct conninfo*) ; 
 int /*<<< orphan*/  free_proc (struct procinfo*) ; 
 struct procinfo* search_proc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reapchild_conn(pid_t pid)
{
	struct procinfo *proc;
	struct conninfo *conn;
	int i;

	if ((proc = search_proc(pid, 0)) == NULL)
		return;
	if ((conn = proc->pr_conn) == NULL)
		return;
	for (i = 0; i < conn->co_numchild; ++i)
		if (conn->co_proc[i] == proc) {
			conn->co_proc[i] = conn->co_proc[--conn->co_numchild];
			break;
		}
	free_proc(proc);
	free_conn(conn);
}