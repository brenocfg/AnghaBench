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
struct receive_writer_arg {scalar_t__ err; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cv; int /*<<< orphan*/  done; int /*<<< orphan*/  q; } ;
struct receive_record_arg {int payload_size; struct receive_record_arg* payload; int /*<<< orphan*/ * write_buf; int /*<<< orphan*/  eos_marker; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 struct receive_record_arg* bqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_return_arcbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (struct receive_record_arg*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ receive_process_record (struct receive_writer_arg*,struct receive_record_arg*) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
receive_writer_thread(void *arg)
{
	struct receive_writer_arg *rwa = arg;
	struct receive_record_arg *rrd;
	for (rrd = bqueue_dequeue(&rwa->q); !rrd->eos_marker;
	    rrd = bqueue_dequeue(&rwa->q)) {
		/*
		 * If there's an error, the main thread will stop putting things
		 * on the queue, but we need to clear everything in it before we
		 * can exit.
		 */
		if (rwa->err == 0) {
			rwa->err = receive_process_record(rwa, rrd);
		} else if (rrd->write_buf != NULL) {
			dmu_return_arcbuf(rrd->write_buf);
			rrd->write_buf = NULL;
			rrd->payload = NULL;
		} else if (rrd->payload != NULL) {
			kmem_free(rrd->payload, rrd->payload_size);
			rrd->payload = NULL;
		}
		kmem_free(rrd, sizeof (*rrd));
	}
	kmem_free(rrd, sizeof (*rrd));
	mutex_enter(&rwa->mutex);
	rwa->done = B_TRUE;
	cv_signal(&rwa->cv);
	mutex_exit(&rwa->mutex);
	thread_exit();
}