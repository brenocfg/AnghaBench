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
 int SIGALRM ; 
 int SIGCHLD ; 
 int SIGHUP ; 
 int SIGTERM ; 
 int /*<<< orphan*/  sigalrms ; 
 int /*<<< orphan*/  sigchlds ; 
 int /*<<< orphan*/  sighups ; 
 int /*<<< orphan*/  sigterms ; 

void
auditd_relay_signal(int signal)
{
        if (signal == SIGHUP)
                sighups++;
        if (signal == SIGTERM)
                sigterms++;
        if (signal == SIGCHLD)
                sigchlds++;
	if (signal == SIGALRM)
		sigalrms++;
}