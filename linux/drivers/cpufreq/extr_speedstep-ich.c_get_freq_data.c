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
 unsigned int speedstep_get_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speedstep_processor ; 

__attribute__((used)) static void get_freq_data(void *_speed)
{
	unsigned int *speed = _speed;

	*speed = speedstep_get_frequency(speedstep_processor);
}