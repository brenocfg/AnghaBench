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
#define  SIGALRM 130 
#define  SIGINFO 129 
#define  SIGINT 128 
 int sigalrm ; 
 int siginfo ; 
 int sigint ; 

__attribute__((used)) static void
sig_handler(int sig)
{
	switch (sig) {
	case SIGALRM:
		sigalrm = 1;
		break;
	case SIGINFO:
		siginfo = 1;
		break;
	case SIGINT:
		sigint = 1;
		break;
	}
}