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
 int /*<<< orphan*/  LOG_DAEMON ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  getprogname () ; 
 int log_level ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
log_init(int level)
{

	log_level = level;
	openlog(getprogname(), LOG_NDELAY | LOG_PID, LOG_DAEMON);
}