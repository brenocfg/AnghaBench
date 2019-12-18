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
struct request {TYPE_1__* q; int /*<<< orphan*/  deadline; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 

void blk_abort_request(struct request *req)
{
	/*
	 * All we need to ensure is that timeout scan takes place
	 * immediately and that scan sees the new timeout value.
	 * No need for fancy synchronizations.
	 */
	WRITE_ONCE(req->deadline, jiffies);
	kblockd_schedule_work(&req->q->timeout_work);
}