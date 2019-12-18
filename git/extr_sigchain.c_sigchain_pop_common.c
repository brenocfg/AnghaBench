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
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 

void sigchain_pop_common(void)
{
	sigchain_pop(SIGPIPE);
	sigchain_pop(SIGQUIT);
	sigchain_pop(SIGTERM);
	sigchain_pop(SIGHUP);
	sigchain_pop(SIGINT);
}