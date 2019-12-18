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

/* Variables and functions */
 int __sys_sigsuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_remove_thr_signals (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
_sigsuspend(const sigset_t * set)
{
	sigset_t newset;

	return (__sys_sigsuspend(thr_remove_thr_signals(set, &newset)));
}