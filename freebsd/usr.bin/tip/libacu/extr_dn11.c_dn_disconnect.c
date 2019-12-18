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
 scalar_t__ FD ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 

void
dn_disconnect(void)
{
	sleep(2);
	if (FD > 0)
		ioctl(FD, TIOCCDTR, 0);
	close(FD);
}