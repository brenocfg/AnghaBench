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
struct sec_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct sec_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sec_dev_info* sec_device_get () ; 
 int /*<<< orphan*/  sec_id_lock ; 
 struct sec_queue* sec_queue_alloc_start (struct sec_dev_info*) ; 

struct sec_queue *sec_queue_alloc_start_safe(void)
{
	struct sec_dev_info *info;
	struct sec_queue *queue = ERR_PTR(-ENODEV);

	mutex_lock(&sec_id_lock);
	info = sec_device_get();
	if (!info)
		goto unlock;

	queue = sec_queue_alloc_start(info);

unlock:
	mutex_unlock(&sec_id_lock);

	return queue;
}