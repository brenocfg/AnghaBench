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
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
remove_thr_signals(sigset_t *set)
{
	if (SIGISMEMBER(*set, SIGCANCEL))
		SIGDELSET(*set, SIGCANCEL);
}