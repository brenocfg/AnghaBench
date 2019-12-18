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
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  LINEDISC ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ value (int /*<<< orphan*/ ) ; 

void
linedisc(char *option)
{
	int ld = (int)(intptr_t)value(LINEDISC);

	ioctl(FD, TIOCSETD, &ld);
}