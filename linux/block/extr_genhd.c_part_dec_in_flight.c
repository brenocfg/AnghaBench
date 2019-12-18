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
struct request_queue {int dummy; } ;
struct hd_struct {scalar_t__ partno; } ;
struct TYPE_2__ {struct hd_struct part0; } ;

/* Variables and functions */
 int /*<<< orphan*/ * in_flight ; 
 int /*<<< orphan*/  part_stat_local_dec (struct hd_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* part_to_disk (struct hd_struct*) ; 
 scalar_t__ queue_is_mq (struct request_queue*) ; 

void part_dec_in_flight(struct request_queue *q, struct hd_struct *part, int rw)
{
	if (queue_is_mq(q))
		return;

	part_stat_local_dec(part, in_flight[rw]);
	if (part->partno)
		part_stat_local_dec(&part_to_disk(part)->part0, in_flight[rw]);
}