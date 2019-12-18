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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  pause () ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
main(void)
{

	if (write(STDOUT_FILENO, "started\n", 8) != 8)
		abort();
	for (;;)
		pause();
}