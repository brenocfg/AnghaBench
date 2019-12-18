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
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct sync_file {int /*<<< orphan*/  fence; int /*<<< orphan*/  wq; TYPE_1__ cb; int /*<<< orphan*/  flags; } ;
struct file {struct sync_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  POLL_ENABLED ; 
 scalar_t__ dma_fence_add_callback (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fence_check_cb_func ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t sync_file_poll(struct file *file, poll_table *wait)
{
	struct sync_file *sync_file = file->private_data;

	poll_wait(file, &sync_file->wq, wait);

	if (list_empty(&sync_file->cb.node) &&
	    !test_and_set_bit(POLL_ENABLED, &sync_file->flags)) {
		if (dma_fence_add_callback(sync_file->fence, &sync_file->cb,
					   fence_check_cb_func) < 0)
			wake_up_all(&sync_file->wq);
	}

	return dma_fence_is_signaled(sync_file->fence) ? EPOLLIN : 0;
}