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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int rmtcall (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

int
rmtioctl(int cmd, int count)
{
	char buf[256];

	if (count < 0)
		return (-1);
	(void)snprintf(buf, sizeof (buf), "I%d\n%d\n", cmd, count);
	return (rmtcall("ioctl", buf));
}