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
typedef  int /*<<< orphan*/  xo_syslog_send_t ;
typedef  int /*<<< orphan*/  xo_syslog_open_t ;
typedef  int /*<<< orphan*/  xo_syslog_close_t ;

/* Variables and functions */
 int /*<<< orphan*/  xo_syslog_close ; 
 int /*<<< orphan*/  xo_syslog_open ; 
 int /*<<< orphan*/  xo_syslog_send ; 

void
xo_set_syslog_handler (xo_syslog_open_t open_func,
		       xo_syslog_send_t send_func,
		       xo_syslog_close_t close_func)
{
    xo_syslog_open = open_func;
    xo_syslog_send = send_func;
    xo_syslog_close = close_func;
}