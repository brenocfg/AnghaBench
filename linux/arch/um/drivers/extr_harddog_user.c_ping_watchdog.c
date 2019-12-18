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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int ping_watchdog(int fd)
{
	int n;
	char c = '\n';

	n = write(fd, &c, sizeof(c));
	if (n != sizeof(c)) {
		printk("ping_watchdog - write failed, ret = %d, err = %d\n",
		       n, errno);
		if (n < 0)
			return n;
		return -EIO;
	}
	return 1;

}