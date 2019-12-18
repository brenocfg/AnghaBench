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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  cond_kdestroy () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ftpd_logwtmp (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ logged_in ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ transflag ; 
 int /*<<< orphan*/  ttyline ; 
 scalar_t__ urgflag ; 

void
dologout(int status)
{
    transflag = 0;
    urgflag = 0;
    if (logged_in) {
#if KRB5
	cond_kdestroy();
#endif
	seteuid((uid_t)0); /* No need to check, we call exit() below */
	ftpd_logwtmp(ttyline, "", "");
    }
    /* beware of flushing buffers after a SIGPIPE */
#ifdef XXX
    exit(status);
#else
    _exit(status);
#endif
}