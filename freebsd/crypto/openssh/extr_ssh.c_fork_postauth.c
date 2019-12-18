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
 int /*<<< orphan*/  control_persist_detach () ; 
 scalar_t__ daemon (int,int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fork_after_authentication_flag ; 
 scalar_t__ need_controlpersist_detach ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fork_postauth(void)
{
	if (need_controlpersist_detach)
		control_persist_detach();
	debug("forking to background");
	fork_after_authentication_flag = 0;
	if (daemon(1, 1) < 0)
		fatal("daemon() failed: %.200s", strerror(errno));
}