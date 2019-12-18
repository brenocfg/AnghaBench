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
typedef  int uint16_t ;
struct cs5535_mfgpt_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int MFGPT_SETUP_CMP1 ; 
 int MFGPT_SETUP_CMP2 ; 
 scalar_t__ MFGPT_SETUP_CNTEN ; 
 int /*<<< orphan*/  cs5535_mfgpt_write (struct cs5535_mfgpt_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_timer(struct cs5535_mfgpt_timer *timer)
{
	/* avoid races by clearing CMP1 and CMP2 unconditionally */
	cs5535_mfgpt_write(timer, MFGPT_REG_SETUP,
			(uint16_t) ~MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP1 |
				MFGPT_SETUP_CMP2);
}