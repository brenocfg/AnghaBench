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
typedef  long u64 ;

/* Variables and functions */
 int HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 long get_jiffies_64 () ; 
 int /*<<< orphan*/  nx_huge_pages ; 
 int /*<<< orphan*/  nx_huge_pages_recovery_ratio ; 

__attribute__((used)) static long get_nx_lpage_recovery_timeout(u64 start_time)
{
	return READ_ONCE(nx_huge_pages) && READ_ONCE(nx_huge_pages_recovery_ratio)
		? start_time + 60 * HZ - get_jiffies_64()
		: MAX_SCHEDULE_TIMEOUT;
}