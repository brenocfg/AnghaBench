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
struct TYPE_3__ {unsigned long expires; } ;
struct request_queue {TYPE_1__ timeout; int /*<<< orphan*/  rq_timeout; } ;
struct request {int /*<<< orphan*/  deadline; int /*<<< orphan*/  timeout; int /*<<< orphan*/  rq_flags; struct request_queue* q; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RQF_TIMED_OUT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long blk_rq_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  round_jiffies_up (unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void blk_add_timer(struct request *req)
{
	struct request_queue *q = req->q;
	unsigned long expiry;

	/*
	 * Some LLDs, like scsi, peek at the timeout to prevent a
	 * command from being retried forever.
	 */
	if (!req->timeout)
		req->timeout = q->rq_timeout;

	req->rq_flags &= ~RQF_TIMED_OUT;

	expiry = jiffies + req->timeout;
	WRITE_ONCE(req->deadline, expiry);

	/*
	 * If the timer isn't already pending or this timeout is earlier
	 * than an existing one, modify the timer. Round up to next nearest
	 * second.
	 */
	expiry = blk_rq_timeout(round_jiffies_up(expiry));

	if (!timer_pending(&q->timeout) ||
	    time_before(expiry, q->timeout.expires)) {
		unsigned long diff = q->timeout.expires - expiry;

		/*
		 * Due to added timer slack to group timers, the timer
		 * will often be a little in front of what we asked for.
		 * So apply some tolerance here too, otherwise we keep
		 * modifying the timer because expires for value X
		 * will be X + something.
		 */
		if (!timer_pending(&q->timeout) || (diff >= HZ / 2))
			mod_timer(&q->timeout, expiry);
	}

}