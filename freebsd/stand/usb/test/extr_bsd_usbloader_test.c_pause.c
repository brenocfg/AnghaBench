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
 int hz ; 
 int /*<<< orphan*/  usleep (int) ; 

int
pause(const char *what, int timeout)
{
	if (timeout == 0)
		timeout = 1;

	usleep((1000000 / hz) * timeout);

	return (0);
}