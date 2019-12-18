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
 scalar_t__ _tftp_logtostdout ; 
 int /*<<< orphan*/  closelog () ; 

void
tftp_closelog(void)
{

	if (_tftp_logtostdout == 0)
		closelog();
}