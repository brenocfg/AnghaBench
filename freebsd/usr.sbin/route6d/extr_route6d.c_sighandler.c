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
#define  SIGHUP 132 
#define  SIGINT 131 
#define  SIGQUIT 130 
#define  SIGTERM 129 
#define  SIGUSR1 128 
 int /*<<< orphan*/  seenalrm ; 
 int /*<<< orphan*/  seenquit ; 
 int /*<<< orphan*/  seenusr1 ; 

__attribute__((used)) static void
sighandler(int signo)
{

	switch (signo) {
	case SIGALRM:
		seenalrm++;
		break;
	case SIGQUIT:
	case SIGTERM:
		seenquit++;
		break;
	case SIGUSR1:
	case SIGHUP:
	case SIGINT:
		seenusr1++;
		break;
	}
}