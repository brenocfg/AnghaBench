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

/* Variables and functions */
 scalar_t__ FD_MOTOR_OFF_DELAY ; 
 scalar_t__ MotorOffTrys ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  motor_off_timer ; 

__attribute__((used)) static inline void start_motor_off_timer(void)
{
	mod_timer(&motor_off_timer, jiffies + FD_MOTOR_OFF_DELAY);
	MotorOffTrys = 0;
}