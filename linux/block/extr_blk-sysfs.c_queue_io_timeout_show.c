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
struct request_queue {int /*<<< orphan*/  rq_timeout; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t queue_io_timeout_show(struct request_queue *q, char *page)
{
	return sprintf(page, "%u\n", jiffies_to_msecs(q->rq_timeout));
}