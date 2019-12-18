#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct http_worker_description {int /*<<< orphan*/  hwd_count; int /*<<< orphan*/  hwd_errorcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  run_done; int /*<<< orphan*/  path; int /*<<< orphan*/  sin; int /*<<< orphan*/  start_barrier; } ;

/* Variables and functions */
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ http_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_barrier_wait () ; 
 TYPE_1__* statep ; 
 scalar_t__ threaded ; 

__attribute__((used)) static void *
http_worker(void *arg)
{
	struct http_worker_description *hwdp;
	int ret;

	if (threaded) {
		ret = pthread_barrier_wait(&statep->start_barrier);
		if (ret != 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD)
			err(-1, "pthread_barrier_wait");
	} else {
		signal_barrier_wait();
	}

	hwdp = arg;
	while (!statep->run_done) {
		if (http_fetch(&statep->sin, statep->path, QUIET) < 0) {
			hwdp->hwd_errorcount++;
			continue;
		}
		/* Don't count transfers that didn't finish in time. */
		if (!statep->run_done)
			hwdp->hwd_count++;
	}

	if (threaded)
		return (NULL);
	else
		exit(0);
}