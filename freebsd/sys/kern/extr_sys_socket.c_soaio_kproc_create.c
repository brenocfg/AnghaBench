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
struct proc {int dummy; } ;

/* Variables and functions */
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int kproc_create (int /*<<< orphan*/ ,void*,struct proc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ soaio_idle ; 
 int /*<<< orphan*/  soaio_jobs_lock ; 
 int /*<<< orphan*/  soaio_kproc_loop ; 
 int /*<<< orphan*/  soaio_kproc_unr ; 
 scalar_t__ soaio_max_procs ; 
 scalar_t__ soaio_num_procs ; 
 scalar_t__ soaio_queued ; 
 scalar_t__ soaio_starting ; 
 scalar_t__ soaio_target_procs ; 

__attribute__((used)) static void
soaio_kproc_create(void *context, int pending)
{
	struct proc *p;
	int error, id;

	mtx_lock(&soaio_jobs_lock);
	for (;;) {
		if (soaio_num_procs < soaio_target_procs) {
			/* Must create */
		} else if (soaio_num_procs >= soaio_max_procs) {
			/*
			 * Hit the limit on kernel processes, don't
			 * create another one.
			 */
			break;
		} else if (soaio_queued <= soaio_idle + soaio_starting) {
			/*
			 * No more AIO jobs waiting for a process to be
			 * created, so stop.
			 */
			break;
		}
		soaio_starting++;
		mtx_unlock(&soaio_jobs_lock);

		id = alloc_unr(soaio_kproc_unr);
		error = kproc_create(soaio_kproc_loop, (void *)(intptr_t)id,
		    &p, 0, 0, "soaiod%d", id);
		if (error != 0) {
			free_unr(soaio_kproc_unr, id);
			mtx_lock(&soaio_jobs_lock);
			soaio_starting--;
			break;
		}

		mtx_lock(&soaio_jobs_lock);
		soaio_num_procs++;
	}
	mtx_unlock(&soaio_jobs_lock);
}