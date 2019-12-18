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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int __sys_sigwaitinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr_remove_thr_signals (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
_sigwaitinfo(const sigset_t *set, siginfo_t *info)
{
	sigset_t newset;

	return (__sys_sigwaitinfo(thr_remove_thr_signals(set, &newset), info));
}