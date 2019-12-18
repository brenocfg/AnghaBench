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
struct request_queue {int dummy; } ;
struct mq_inflight {unsigned int* inflight; struct hd_struct* part; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_check_inflight ; 
 int /*<<< orphan*/  blk_mq_queue_tag_busy_iter (struct request_queue*,int /*<<< orphan*/ ,struct mq_inflight*) ; 

unsigned int blk_mq_in_flight(struct request_queue *q, struct hd_struct *part)
{
	unsigned inflight[2];
	struct mq_inflight mi = { .part = part, .inflight = inflight, };

	inflight[0] = inflight[1] = 0;
	blk_mq_queue_tag_busy_iter(q, blk_mq_check_inflight, &mi);

	return inflight[0];
}