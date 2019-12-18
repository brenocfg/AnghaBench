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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
__arc4random_stir_fbsd11(void)
{
	static bool warned = false;

	if (!warned)
		syslog(LOG_DEBUG, "Deprecated function arc4random_stir() called");
	warned = true;
}