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
 int called ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
signal_cb_swp(int sig, short event, void *arg)
{
	called++;
	if (called < 5)
		kill(getpid(), sig);
	else
		event_loopexit(NULL);
}