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
#define  SIGALRM 133 
#define  SIGCHLD 132 
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int sig_alrm ; 
 int sig_chld ; 
 int sig_ign ; 
 int sig_term ; 

__attribute__((used)) static void
sig_handler(int signo)
{
	if (sig_ign != 0 && signo == sig_ign) {
		sig_ign = 0;
		return;
	}

	switch(signo) {
	case 0:
	case SIGINT:
	case SIGHUP:
	case SIGQUIT:
	case SIGTERM:
		sig_term = signo;
		break;
	case SIGCHLD:
		sig_chld = 1;
		break;
	case SIGALRM:
		sig_alrm = 1;
		break;
	}
}