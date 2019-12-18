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
typedef  int /*<<< orphan*/  ucontext_t ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */

int
__signalcontext(ucontext_t *ucp, int sig, __sighandler_t *func)
{
	/* XXXMIPS: Implement me */
	return (0);
}