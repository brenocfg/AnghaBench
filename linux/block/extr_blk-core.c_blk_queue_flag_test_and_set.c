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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 

bool blk_queue_flag_test_and_set(unsigned int flag, struct request_queue *q)
{
	return test_and_set_bit(flag, &q->queue_flags);
}