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
struct rtc_cfg {int /*<<< orphan*/ * trigger_polarity; int /*<<< orphan*/ * alarm_polarity; int /*<<< orphan*/  pulse_realign; int /*<<< orphan*/  invert_output_clk_phase; int /*<<< orphan*/  invert_input_clk_phase; int /*<<< orphan*/  src_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ALARM_POLARITY ; 
 int /*<<< orphan*/  DEFAULT_INVERT_INPUT_CLK_PHASE ; 
 int /*<<< orphan*/  DEFAULT_INVERT_OUTPUT_CLK_PHASE ; 
 int /*<<< orphan*/  DEFAULT_PULSE_REALIGN ; 
 int /*<<< orphan*/  DEFAULT_SRC_CLOCK ; 
 int /*<<< orphan*/  DEFAULT_TRIGGER_POLARITY ; 
 int FMAN_RTC_MAX_NUM_OF_ALARMS ; 
 int FMAN_RTC_MAX_NUM_OF_EXT_TRIGGERS ; 

void fman_rtc_defconfig(struct rtc_cfg *cfg)
{
	int i;
	cfg->src_clk = DEFAULT_SRC_CLOCK;
	cfg->invert_input_clk_phase = DEFAULT_INVERT_INPUT_CLK_PHASE;
	cfg->invert_output_clk_phase = DEFAULT_INVERT_OUTPUT_CLK_PHASE;
	cfg->pulse_realign = DEFAULT_PULSE_REALIGN;
	for (i = 0; i < FMAN_RTC_MAX_NUM_OF_ALARMS; i++)
		cfg->alarm_polarity[i] = DEFAULT_ALARM_POLARITY;
	for (i = 0; i < FMAN_RTC_MAX_NUM_OF_EXT_TRIGGERS; i++)
		cfg->trigger_polarity[i] = DEFAULT_TRIGGER_POLARITY;
}