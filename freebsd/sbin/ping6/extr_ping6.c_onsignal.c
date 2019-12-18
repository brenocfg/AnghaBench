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
 int /*<<< orphan*/  seeninfo ; 
 int /*<<< orphan*/  seenint ; 

__attribute__((used)) static void
onsignal(int sig)
{

	switch (sig) {
	case SIGINT:
	case SIGALRM:
		seenint++;
		break;
#ifdef SIGINFO
	case SIGINFO:
		seeninfo++;
		break;
#endif
	}
}