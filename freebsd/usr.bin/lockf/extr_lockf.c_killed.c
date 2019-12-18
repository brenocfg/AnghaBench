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
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
killed(int sig)
{

	cleanup();
	signal(sig, SIG_DFL);
	if (kill(getpid(), sig) == -1)
		err(EX_OSERR, "kill failed");
}