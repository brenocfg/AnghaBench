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
struct pt_time_cal {int /*<<< orphan*/  min_fcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  memset (struct pt_time_cal*,int /*<<< orphan*/ ,int) ; 

void pt_tcal_init(struct pt_time_cal *tcal)
{
	if (!tcal)
		return;

	memset(tcal, 0, sizeof(*tcal));

	tcal->min_fcr = UINT64_MAX;
}