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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGRETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ doing_useful_work ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  killpg (scalar_t__,int) ; 
 scalar_t__ pgrp ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int term_flag ; 

__attribute__((used)) static RETSIGTYPE
terminate(int sig)
{
    if(getpid() == pgrp) {
	/* parent */
	term_flag = 1;
	signal(sig, SIG_IGN);
	killpg(pgrp, sig);
    } else {
	/* child */
	if(doing_useful_work)
	    term_flag = 1;
	else
	    exit(0);
    }
    SIGRETURN(0);
}