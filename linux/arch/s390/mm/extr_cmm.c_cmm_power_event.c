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
 int NOTIFY_DONE ; 
#define  PM_HIBERNATION_PREPARE 129 
#define  PM_POST_HIBERNATION 128 
 int cmm_resume () ; 
 int cmm_suspend () ; 

__attribute__((used)) static int cmm_power_event(struct notifier_block *this,
			   unsigned long event, void *ptr)
{
	switch (event) {
	case PM_POST_HIBERNATION:
		return cmm_resume();
	case PM_HIBERNATION_PREPARE:
		return cmm_suspend();
	default:
		return NOTIFY_DONE;
	}
}