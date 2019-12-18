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
struct tftp_stats {int /*<<< orphan*/  tstart; scalar_t__ amount; scalar_t__ blocks; scalar_t__ retries; scalar_t__ rollovers; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
stats_init(struct tftp_stats *ts)
{

	ts->amount = 0;
	ts->rollovers = 0;
	ts->retries = 0;
	ts->blocks = 0;
	ts->amount = 0;
	gettimeofday(&(ts->tstart), NULL);
}