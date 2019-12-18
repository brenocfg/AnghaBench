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
typedef  int /*<<< orphan*/  uint8_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_rtc_data {int offset; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_RTC_WRITE ; 
 int /*<<< orphan*/  bzero (struct vm_rtc_data*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_rtc_data*) ; 

int
vm_rtc_write(struct vmctx *ctx, int offset, uint8_t value)
{
	struct vm_rtc_data rtcdata;
	int error;

	bzero(&rtcdata, sizeof(struct vm_rtc_data));
	rtcdata.offset = offset;
	rtcdata.value = value;
	error = ioctl(ctx->fd, VM_RTC_WRITE, &rtcdata);
	return (error);
}