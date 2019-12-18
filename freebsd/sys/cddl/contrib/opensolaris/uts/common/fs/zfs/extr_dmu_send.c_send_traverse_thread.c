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
struct send_thread_arg {int error_code; int /*<<< orphan*/  q; int /*<<< orphan*/  flags; int /*<<< orphan*/  resume; int /*<<< orphan*/  fromtxg; int /*<<< orphan*/ * ds; } ;
struct send_block_record {int /*<<< orphan*/  eos_marker; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int EINTR ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bqueue_enqueue (int /*<<< orphan*/ *,struct send_block_record*,int) ; 
 struct send_block_record* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_cb ; 
 int /*<<< orphan*/  thread_exit () ; 
 int traverse_dataset_resume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct send_thread_arg*) ; 

__attribute__((used)) static void
send_traverse_thread(void *arg)
{
	struct send_thread_arg *st_arg = arg;
	int err;
	struct send_block_record *data;

	if (st_arg->ds != NULL) {
		err = traverse_dataset_resume(st_arg->ds,
		    st_arg->fromtxg, &st_arg->resume,
		    st_arg->flags, send_cb, st_arg);

		if (err != EINTR)
			st_arg->error_code = err;
	}
	data = kmem_zalloc(sizeof (*data), KM_SLEEP);
	data->eos_marker = B_TRUE;
	bqueue_enqueue(&st_arg->q, data, 1);
	thread_exit();
}