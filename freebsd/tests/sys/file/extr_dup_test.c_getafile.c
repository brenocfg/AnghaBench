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
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ftruncate (int,int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static int
getafile(void)
{
	int fd;

	char temp[] = "/tmp/dup2XXXXXXXXX";
	if ((fd = mkstemp(temp)) < 0)
		err(1, "mkstemp");
	remove(temp);
	if (ftruncate(fd, 1024) != 0)
		err(1, "ftruncate");
	return (fd);
}