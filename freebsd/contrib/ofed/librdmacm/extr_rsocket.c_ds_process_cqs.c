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
struct rsocket {int cq_armed; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  cq_wait_lock; } ;

/* Variables and functions */
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int ds_get_cq_event (struct rsocket*) ; 
 int /*<<< orphan*/  ds_poll_cqs (struct rsocket*) ; 
 int /*<<< orphan*/  ds_req_notify_cqs (struct rsocket*) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds_process_cqs(struct rsocket *rs, int nonblock, int (*test)(struct rsocket *rs))
{
	int ret = 0;

	fastlock_acquire(&rs->cq_lock);
	do {
		ds_poll_cqs(rs);
		if (test(rs)) {
			ret = 0;
			break;
		} else if (nonblock) {
			ret = ERR(EWOULDBLOCK);
		} else if (!rs->cq_armed) {
			ds_req_notify_cqs(rs);
			rs->cq_armed = 1;
		} else {
			fastlock_acquire(&rs->cq_wait_lock);
			fastlock_release(&rs->cq_lock);

			ret = ds_get_cq_event(rs);
			fastlock_release(&rs->cq_wait_lock);
			fastlock_acquire(&rs->cq_lock);
		}
	} while (!ret);

	fastlock_release(&rs->cq_lock);
	return ret;
}