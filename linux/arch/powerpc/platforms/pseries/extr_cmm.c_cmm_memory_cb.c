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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  MEM_CANCEL_OFFLINE 133 
#define  MEM_CANCEL_ONLINE 132 
#define  MEM_GOING_OFFLINE 131 
#define  MEM_GOING_ONLINE 130 
#define  MEM_OFFLINE 129 
#define  MEM_ONLINE 128 
 int /*<<< orphan*/  cmm_dbg (char*) ; 
 int cmm_mem_going_offline (void*) ; 
 int /*<<< orphan*/  hotplug_mutex ; 
 int hotplug_occurred ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int notifier_from_errno (int) ; 

__attribute__((used)) static int cmm_memory_cb(struct notifier_block *self,
			unsigned long action, void *arg)
{
	int ret = 0;

	switch (action) {
	case MEM_GOING_OFFLINE:
		mutex_lock(&hotplug_mutex);
		hotplug_occurred = 1;
		ret = cmm_mem_going_offline(arg);
		break;
	case MEM_OFFLINE:
	case MEM_CANCEL_OFFLINE:
		mutex_unlock(&hotplug_mutex);
		cmm_dbg("Memory offline operation complete.\n");
		break;
	case MEM_GOING_ONLINE:
	case MEM_ONLINE:
	case MEM_CANCEL_ONLINE:
		break;
	}

	return notifier_from_errno(ret);
}