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
struct servtab {int /*<<< orphan*/ * se_conn; } ;
struct conninfo {int co_numchild; int /*<<< orphan*/ * co_proc; } ;

/* Variables and functions */
 struct conninfo* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int PERIPSIZE ; 
 int /*<<< orphan*/  free_conn (struct conninfo*) ; 
 int /*<<< orphan*/  free_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_connlist(struct servtab *sep)
{
	struct conninfo *conn;
	int i, j;

	for (i = 0; i < PERIPSIZE; ++i) {
		while ((conn = LIST_FIRST(&sep->se_conn[i])) != NULL) {
			for (j = 0; j < conn->co_numchild; ++j)
				free_proc(conn->co_proc[j]);
			conn->co_numchild = 0;
			free_conn(conn);
		}
	}
}