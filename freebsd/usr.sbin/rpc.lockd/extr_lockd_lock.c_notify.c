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
 int /*<<< orphan*/  debuglog (char*,...) ; 
 int /*<<< orphan*/  do_clear (char const*) ; 
 int /*<<< orphan*/  siglock () ; 
 int /*<<< orphan*/  sigunlock () ; 

void
notify(const char *hostname, const int state)
{
	debuglog("notify from %s, new state %d", hostname, state);

	siglock();
	do_clear(hostname);
	sigunlock();

	debuglog("Leaving notify\n");
}