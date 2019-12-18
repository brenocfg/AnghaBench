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
 int /*<<< orphan*/  CHILD_REQUIRE (int) ; 
 int /*<<< orphan*/  SIGABRT ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sigusr1_step_handler(int sig)
{

	CHILD_REQUIRE(sig == SIGUSR1);
	raise(SIGABRT);
}