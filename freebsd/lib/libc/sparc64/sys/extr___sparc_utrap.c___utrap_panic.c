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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  __utrap_kill_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __utrap_write (char const*) ; 

void
__utrap_panic(const char *msg)
{

	__utrap_write(msg);
	__utrap_write("\n");
	__utrap_kill_self(SIGKILL);
}