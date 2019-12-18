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
 int /*<<< orphan*/  NOCONN ; 
 int /*<<< orphan*/  close (int) ; 
 int xo_logfile ; 
 int /*<<< orphan*/  xo_status ; 
 int /*<<< orphan*/  xo_syslog_close () ; 

__attribute__((used)) static void
xo_disconnect_log (void)
{
    if (xo_syslog_close) {
	xo_syslog_close();
	return;
    }

    /*
     * If the user closed the FD and opened another in the same slot,
     * that's their problem.  They should close it before calling on
     * system services.
     */
    if (xo_logfile != -1) {
        close(xo_logfile);
        xo_logfile = -1;
    }
    xo_status = NOCONN;            /* retry connect */
}