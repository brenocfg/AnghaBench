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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  l_sigset_t ;

/* Variables and functions */
 scalar_t__ LINUX_SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int LINUX_SIGRTMAX ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int linux_to_bsd_signal (int) ; 

void
linux_to_bsd_sigset(l_sigset_t *lss, sigset_t *bss)
{
	int b, l;

	SIGEMPTYSET(*bss);
	for (l = 1; l <= LINUX_SIGRTMAX; l++) {
		if (LINUX_SIGISMEMBER(*lss, l)) {
			b = linux_to_bsd_signal(l);
			if (b)
				SIGADDSET(*bss, b);
		}
	}
}