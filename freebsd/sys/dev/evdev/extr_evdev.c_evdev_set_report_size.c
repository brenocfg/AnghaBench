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
struct evdev_dev {size_t ev_report_size; } ;

/* Variables and functions */
 size_t ABS_CNT ; 
 int EINVAL ; 
 size_t FF_CNT ; 
 size_t KEY_CNT ; 
 size_t LED_CNT ; 
 size_t MAX_MT_SLOTS ; 
 size_t MSC_CNT ; 
 size_t MT_CNT ; 
 size_t REL_CNT ; 
 size_t SND_CNT ; 
 size_t SW_CNT ; 

int
evdev_set_report_size(struct evdev_dev *evdev, size_t report_size)
{
	if (report_size > KEY_CNT + REL_CNT + ABS_CNT + MAX_MT_SLOTS * MT_CNT +
	    MSC_CNT + LED_CNT + SND_CNT + SW_CNT + FF_CNT)
		return (EINVAL);

	evdev->ev_report_size = report_size;
	return (0);
}