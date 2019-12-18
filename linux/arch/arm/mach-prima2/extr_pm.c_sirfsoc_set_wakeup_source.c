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
typedef  int u32 ;

/* Variables and functions */
 int RTC_ALARM0_B ; 
 int RTC_ALARM1_B ; 
 scalar_t__ SIRFSOC_PWRC_TRIGGER_EN ; 
 int X_ON_KEY_B ; 
 scalar_t__ sirfsoc_pwrc_base ; 
 int sirfsoc_rtc_iobrg_readl (scalar_t__) ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_writel (int,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_set_wakeup_source(void)
{
	u32 pwr_trigger_en_reg;
	pwr_trigger_en_reg = sirfsoc_rtc_iobrg_readl(sirfsoc_pwrc_base +
		SIRFSOC_PWRC_TRIGGER_EN);
#define X_ON_KEY_B (1 << 0)
#define RTC_ALARM0_B (1 << 2)
#define RTC_ALARM1_B (1 << 3)
	sirfsoc_rtc_iobrg_writel(pwr_trigger_en_reg | X_ON_KEY_B |
		RTC_ALARM0_B | RTC_ALARM1_B,
		sirfsoc_pwrc_base + SIRFSOC_PWRC_TRIGGER_EN);
}