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
struct cpufreq_frequency_table {scalar_t__ frequency; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_TABLE_END ; 

__attribute__((used)) static inline u32 get_table_count(struct cpufreq_frequency_table *table)
{
	int count;

	for (count = 0; table[count].frequency != CPUFREQ_TABLE_END; count++)
		;

	return count;
}