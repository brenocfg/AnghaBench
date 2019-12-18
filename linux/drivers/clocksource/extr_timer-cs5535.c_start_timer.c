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
 int /*<<< orphan*/  MFGPT_REG_CMP2 ; 
 int /*<<< orphan*/  MFGPT_REG_COUNTER ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int MFGPT_SETUP_CMP2 ; 
 int MFGPT_SETUP_CNTEN ; 
 int /*<<< orphan*/  cs5535_mfgpt_write (struct cs5535_mfgpt_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void start_timer(struct cs5535_mfgpt_timer *timer, uint16_t delta)
{
	cs5535_mfgpt_write(timer, MFGPT_REG_CMP2, delta);
	cs5535_mfgpt_write(timer, MFGPT_REG_COUNTER, 0);

	cs5535_mfgpt_write(timer, MFGPT_REG_SETUP,
			MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP2);
}