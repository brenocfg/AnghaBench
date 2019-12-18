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
typedef  int uint64_t ;
struct throtl_data {int scale; int low_upgrade_time; int throtl_slice; } ;

/* Variables and functions */
 int jiffies ; 
 scalar_t__ time_after_eq (int,int) ; 

__attribute__((used)) static uint64_t throtl_adjusted_limit(uint64_t low, struct throtl_data *td)
{
	/* arbitrary value to avoid too big scale */
	if (td->scale < 4096 && time_after_eq(jiffies,
	    td->low_upgrade_time + td->scale * td->throtl_slice))
		td->scale = (jiffies - td->low_upgrade_time) / td->throtl_slice;

	return low + (low >> 1) * td->scale;
}