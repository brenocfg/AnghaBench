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
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int strlen (char const*) ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static void
do_write(int fd, const char *buf)
{
	int len = strlen(buf);

	if (write(fd, buf, len) != len)
		err(EX_SOFTWARE, "Could not write to output file");
}