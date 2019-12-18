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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sec_queue_base_init (struct sec_dev_info*,struct sec_queue*,int) ; 
 int /*<<< orphan*/  sec_queue_free_ring_pages (struct sec_queue*) ; 
 int /*<<< orphan*/  sec_queue_hw_init (struct sec_queue*) ; 
 int sec_queue_map_io (struct sec_queue*) ; 
 int sec_queue_res_cfg (struct sec_queue*) ; 

__attribute__((used)) static int sec_queue_config(struct sec_dev_info *info, struct sec_queue *queue,
			    int queue_id)
{
	int ret;

	sec_queue_base_init(info, queue, queue_id);

	ret = sec_queue_res_cfg(queue);
	if (ret)
		return ret;

	ret = sec_queue_map_io(queue);
	if (ret) {
		dev_err(info->dev, "Queue map failed %d\n", ret);
		sec_queue_free_ring_pages(queue);
		return ret;
	}

	sec_queue_hw_init(queue);

	return 0;
}