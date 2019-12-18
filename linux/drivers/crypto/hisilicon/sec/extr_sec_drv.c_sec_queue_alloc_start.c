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
struct sec_queue {int dummy; } ;
struct sec_dev_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sec_queue*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sec_queue*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sec_queue* sec_alloc_queue (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_queue_start (struct sec_queue*) ; 

__attribute__((used)) static struct sec_queue *sec_queue_alloc_start(struct sec_dev_info *info)
{
	struct sec_queue *queue;

	queue = sec_alloc_queue(info);
	if (IS_ERR(queue)) {
		dev_err(info->dev, "alloc sec queue failed! %ld\n",
			PTR_ERR(queue));
		return queue;
	}

	sec_queue_start(queue);

	return queue;
}