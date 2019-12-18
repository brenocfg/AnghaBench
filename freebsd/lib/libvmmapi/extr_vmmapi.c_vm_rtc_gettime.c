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
typedef  int /*<<< orphan*/  time_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_rtc_time {int /*<<< orphan*/  secs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_RTC_GETTIME ; 
 int /*<<< orphan*/  bzero (struct vm_rtc_time*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_rtc_time*) ; 

int
vm_rtc_gettime(struct vmctx *ctx, time_t *secs)
{
	struct vm_rtc_time rtctime;
	int error;

	bzero(&rtctime, sizeof(struct vm_rtc_time));
	error = ioctl(ctx->fd, VM_RTC_GETTIME, &rtctime);
	if (error == 0)
		*secs = rtctime.secs;
	return (error);
}