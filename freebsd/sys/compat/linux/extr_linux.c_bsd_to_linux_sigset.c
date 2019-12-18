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
 int /*<<< orphan*/  LINUX_SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LINUX_SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int SIGRTMAX ; 
 int bsd_to_linux_signal (int) ; 

void
bsd_to_linux_sigset(sigset_t *bss, l_sigset_t *lss)
{
	int b, l;

	LINUX_SIGEMPTYSET(*lss);
	for (b = 1; b <= SIGRTMAX; b++) {
		if (SIGISMEMBER(*bss, b)) {
			l = bsd_to_linux_signal(b);
			if (l)
				LINUX_SIGADDSET(*lss, l);
		}
	}
}