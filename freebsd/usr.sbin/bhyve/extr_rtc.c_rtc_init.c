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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_HMEM_LSB ; 
 int /*<<< orphan*/  RTC_HMEM_MSB ; 
 int /*<<< orphan*/  RTC_HMEM_SB ; 
 int /*<<< orphan*/  RTC_LMEM_LSB ; 
 int /*<<< orphan*/  RTC_LMEM_MSB ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t m_16MB ; 
 size_t m_64KB ; 
 int /*<<< orphan*/  rtc_time (struct vmctx*,int) ; 
 size_t vm_get_highmem_size (struct vmctx*) ; 
 size_t vm_get_lowmem_size (struct vmctx*) ; 
 int vm_rtc_settime (struct vmctx*,int /*<<< orphan*/ ) ; 
 int vm_rtc_write (struct vmctx*,int /*<<< orphan*/ ,size_t) ; 

void
rtc_init(struct vmctx *ctx, int use_localtime)
{	
	size_t himem;
	size_t lomem;
	int err;

	/* XXX init diag/reset code/equipment/checksum ? */

	/*
	 * Report guest memory size in nvram cells as required by UEFI.
	 * Little-endian encoding.
	 * 0x34/0x35 - 64KB chunks above 16MB, below 4GB
	 * 0x5b/0x5c/0x5d - 64KB chunks above 4GB
	 */
	lomem = (vm_get_lowmem_size(ctx) - m_16MB) / m_64KB;
	err = vm_rtc_write(ctx, RTC_LMEM_LSB, lomem);
	assert(err == 0);
	err = vm_rtc_write(ctx, RTC_LMEM_MSB, lomem >> 8);
	assert(err == 0);

	himem = vm_get_highmem_size(ctx) / m_64KB;
	err = vm_rtc_write(ctx, RTC_HMEM_LSB, himem);
	assert(err == 0);
	err = vm_rtc_write(ctx, RTC_HMEM_SB, himem >> 8);
	assert(err == 0);
	err = vm_rtc_write(ctx, RTC_HMEM_MSB, himem >> 16);
	assert(err == 0);

	err = vm_rtc_settime(ctx, rtc_time(ctx, use_localtime));
	assert(err == 0);
}