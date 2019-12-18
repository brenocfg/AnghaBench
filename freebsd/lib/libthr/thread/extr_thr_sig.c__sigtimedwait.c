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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int __sys_sigtimedwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timespec const*) ; 
 int /*<<< orphan*/  thr_remove_thr_signals (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
_sigtimedwait(const sigset_t *set, siginfo_t *info,
	const struct timespec * timeout)
{
	sigset_t newset;

	return (__sys_sigtimedwait(thr_remove_thr_signals(set, &newset), info,
	    timeout));
}