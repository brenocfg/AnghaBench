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
struct trussinfo {int /*<<< orphan*/ * curthread; } ;
struct procinfo {int /*<<< orphan*/  threadlist; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 struct procinfo* find_proc (struct trussinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_exit_thread(struct trussinfo *info, pid_t pid)
{
	struct procinfo *p;

	p = find_proc(info, pid);
	assert(p != NULL);

	info->curthread = LIST_FIRST(&p->threadlist);
	assert(info->curthread != NULL);
	assert(LIST_NEXT(info->curthread, entries) == NULL);
}