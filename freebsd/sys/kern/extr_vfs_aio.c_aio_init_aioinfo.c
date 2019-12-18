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
struct proc {int /*<<< orphan*/  kaio_mtx; struct proc* p_aioinfo; int /*<<< orphan*/  kaio_sync_task; int /*<<< orphan*/  kaio_task; int /*<<< orphan*/  kaio_syncready; int /*<<< orphan*/  kaio_syncqueue; int /*<<< orphan*/  kaio_liojoblist; int /*<<< orphan*/  kaio_jobqueue; int /*<<< orphan*/  kaio_done; int /*<<< orphan*/  kaio_all; scalar_t__ kaio_buffer_count; scalar_t__ kaio_count; scalar_t__ kaio_active_count; scalar_t__ kaio_flags; } ;
struct kaioinfo {int /*<<< orphan*/  kaio_mtx; struct kaioinfo* p_aioinfo; int /*<<< orphan*/  kaio_sync_task; int /*<<< orphan*/  kaio_task; int /*<<< orphan*/  kaio_syncready; int /*<<< orphan*/  kaio_syncqueue; int /*<<< orphan*/  kaio_liojoblist; int /*<<< orphan*/  kaio_jobqueue; int /*<<< orphan*/  kaio_done; int /*<<< orphan*/  kaio_all; scalar_t__ kaio_buffer_count; scalar_t__ kaio_count; scalar_t__ kaio_active_count; scalar_t__ kaio_flags; } ;

/* Variables and functions */
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MTX_DEF ; 
 int MTX_NEW ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  aio_kick_helper ; 
 int /*<<< orphan*/  aio_newproc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_schedule_fsync ; 
 int /*<<< orphan*/  kaio_zone ; 
 int /*<<< orphan*/  max_aio_procs ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ num_aio_procs ; 
 int /*<<< orphan*/  target_aio_procs ; 
 struct proc* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct proc*) ; 

void
aio_init_aioinfo(struct proc *p)
{
	struct kaioinfo *ki;

	ki = uma_zalloc(kaio_zone, M_WAITOK);
	mtx_init(&ki->kaio_mtx, "aiomtx", NULL, MTX_DEF | MTX_NEW);
	ki->kaio_flags = 0;
	ki->kaio_active_count = 0;
	ki->kaio_count = 0;
	ki->kaio_buffer_count = 0;
	TAILQ_INIT(&ki->kaio_all);
	TAILQ_INIT(&ki->kaio_done);
	TAILQ_INIT(&ki->kaio_jobqueue);
	TAILQ_INIT(&ki->kaio_liojoblist);
	TAILQ_INIT(&ki->kaio_syncqueue);
	TAILQ_INIT(&ki->kaio_syncready);
	TASK_INIT(&ki->kaio_task, 0, aio_kick_helper, p);
	TASK_INIT(&ki->kaio_sync_task, 0, aio_schedule_fsync, ki);
	PROC_LOCK(p);
	if (p->p_aioinfo == NULL) {
		p->p_aioinfo = ki;
		PROC_UNLOCK(p);
	} else {
		PROC_UNLOCK(p);
		mtx_destroy(&ki->kaio_mtx);
		uma_zfree(kaio_zone, ki);
	}

	while (num_aio_procs < MIN(target_aio_procs, max_aio_procs))
		aio_newproc(NULL);
}