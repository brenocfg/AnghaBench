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
struct request_queue {int poll_nsec; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int BLK_MQ_POLL_CLASSIC ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t queue_poll_delay_show(struct request_queue *q, char *page)
{
	int val;

	if (q->poll_nsec == BLK_MQ_POLL_CLASSIC)
		val = BLK_MQ_POLL_CLASSIC;
	else
		val = q->poll_nsec / 1000;

	return sprintf(page, "%d\n", val);
}