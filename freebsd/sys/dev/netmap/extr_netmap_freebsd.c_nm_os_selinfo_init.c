#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_6__ {scalar_t__ kqueue_users; int /*<<< orphan*/  m; TYPE_1__ si; int /*<<< orphan*/  mtxname; int /*<<< orphan*/ * ntfytq; int /*<<< orphan*/  ntfytask; } ;
typedef  TYPE_2__ NM_SELINFO_T ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_kqueue_notify ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/ * taskqueue_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

int nm_os_selinfo_init(NM_SELINFO_T *si, const char *name) {
	int err;

	TASK_INIT(&si->ntfytask, 0, nm_kqueue_notify, si);
	si->ntfytq = taskqueue_create(name, M_NOWAIT,
	    taskqueue_thread_enqueue, &si->ntfytq);
	if (si->ntfytq == NULL)
		return -ENOMEM;
	err = taskqueue_start_threads(&si->ntfytq, 1, PI_NET, "tq %s", name);
	if (err) {
		taskqueue_free(si->ntfytq);
		si->ntfytq = NULL;
		return err;
	}

	snprintf(si->mtxname, sizeof(si->mtxname), "nmkl%s", name);
	mtx_init(&si->m, si->mtxname, NULL, MTX_DEF);
	knlist_init_mtx(&si->si.si_note, &si->m);
	si->kqueue_users = 0;

	return (0);
}