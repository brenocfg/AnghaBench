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
struct rtc_time {int dummy; } ;
typedef  int /*<<< orphan*/  rtc_tm ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_TIME ; 
 int EACCES ; 
 int EFAULT ; 
 int ENOTTY ; 
#define  RTC_RD_TIME 129 
#define  RTC_SET_TIME 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct rtc_time*,struct rtc_time*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,struct rtc_time*,int) ; 
 int /*<<< orphan*/  get_rtc_time (struct rtc_time*) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_rtc_time (struct rtc_time*) ; 

__attribute__((used)) static int rtc_do_ioctl(unsigned int cmd, unsigned long arg)
{
	struct rtc_time rtc_tm;

	switch (cmd) {
		case RTC_RD_TIME:
			memset(&rtc_tm, 0, sizeof(struct rtc_time));
			get_rtc_time(&rtc_tm);
			if (copy_to_user((void *)arg, &rtc_tm, sizeof(rtc_tm)))
				return -EFAULT;
			break;

		case RTC_SET_TIME:
			if (!capable(CAP_SYS_TIME))
				return -EACCES;

			if (copy_from_user(&rtc_tm, (struct rtc_time *)arg,
					   sizeof(struct rtc_time)))
				return -EFAULT;

			set_rtc_time(&rtc_tm);
			break;

		default:
			return -ENOTTY;
	}

	return 0;
}