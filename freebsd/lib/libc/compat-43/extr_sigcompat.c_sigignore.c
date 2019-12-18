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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_IGN ; 
 int __libc_sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 

int
sigignore(int sig)
{
	struct sigaction sa;

	bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	return (__libc_sigaction(sig, &sa, NULL));
}