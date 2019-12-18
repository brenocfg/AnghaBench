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
 unsigned int NSIG ; 
 int /*<<< orphan*/  STALL_TIMEOUT ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  emergency (char*,char*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 char** sys_siglist ; 

__attribute__((used)) static void
disaster(int sig)
{

	emergency("fatal signal: %s",
	    (unsigned)sig < NSIG ? sys_siglist[sig] : "unknown signal");

	sleep(STALL_TIMEOUT);
	_exit(sig);		/* reboot */
}