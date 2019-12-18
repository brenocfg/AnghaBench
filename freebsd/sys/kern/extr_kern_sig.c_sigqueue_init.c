#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sq_flags; struct proc* sq_proc; int /*<<< orphan*/  sq_list; int /*<<< orphan*/  sq_ptrace; int /*<<< orphan*/  sq_kill; int /*<<< orphan*/  sq_signals; } ;
typedef  TYPE_1__ sigqueue_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQ_INIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

void
sigqueue_init(sigqueue_t *list, struct proc *p)
{
	SIGEMPTYSET(list->sq_signals);
	SIGEMPTYSET(list->sq_kill);
	SIGEMPTYSET(list->sq_ptrace);
	TAILQ_INIT(&list->sq_list);
	list->sq_proc = p;
	list->sq_flags = SQ_INIT;
}