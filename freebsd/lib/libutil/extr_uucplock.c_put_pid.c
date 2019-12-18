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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 
 int write (int,char*,size_t) ; 

__attribute__((used)) static int
put_pid(int fd, pid_t pid)
{
	char buf[32];
	int len;

	len = sprintf (buf, "%10d\n", (int)pid);
	return write (fd, buf, (size_t)len) == len;
}