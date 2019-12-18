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
struct s3c2416_data {int /*<<< orphan*/  armclk; scalar_t__ is_dvs; } ;

/* Variables and functions */
 unsigned int FREQ_DVS ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct s3c2416_data s3c2416_cpufreq ; 

__attribute__((used)) static unsigned int s3c2416_cpufreq_get_speed(unsigned int cpu)
{
	struct s3c2416_data *s3c_freq = &s3c2416_cpufreq;

	if (cpu != 0)
		return 0;

	/* return our pseudo-frequency when in dvs mode */
	if (s3c_freq->is_dvs)
		return FREQ_DVS;

	return clk_get_rate(s3c_freq->armclk) / 1000;
}