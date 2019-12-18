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
struct tasklet_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ TASKLET_ST_GET (struct tasklet_struct*) ; 
 scalar_t__ TASKLET_ST_IDLE ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

void
tasklet_kill(struct tasklet_struct *ts)
{

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "tasklet_kill() can sleep");

	/* wait until tasklet is no longer busy */
	while (TASKLET_ST_GET(ts) != TASKLET_ST_IDLE)
		pause("W", 1);
}