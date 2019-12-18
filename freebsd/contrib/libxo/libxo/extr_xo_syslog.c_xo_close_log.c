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
 int /*<<< orphan*/  THREAD_LOCK () ; 
 int /*<<< orphan*/  THREAD_UNLOCK () ; 
 int /*<<< orphan*/  close (int) ; 
 int xo_logfile ; 
 int /*<<< orphan*/ * xo_logtag ; 
 int /*<<< orphan*/  xo_status ; 

void
xo_close_log (void) 
{
    THREAD_LOCK();
    if (xo_logfile != -1) {
        (void) close(xo_logfile);
        xo_logfile = -1;
    }
    xo_logtag = NULL;
    xo_status = NOCONN;
    THREAD_UNLOCK();
}