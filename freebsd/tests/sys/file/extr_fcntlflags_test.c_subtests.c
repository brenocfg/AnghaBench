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
 int CORRECT_O_ACCMODE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  testnum ; 

__attribute__((used)) static void
subtests(const char *path, int omode, const char *omodetext)
{
	int fd, flags1, flags2, flags3;

	fd = open(path, omode);
	if (fd == -1)
		printf("not ok %d - open(\"%s\", %s) failed\n",
		    testnum++, path, omodetext);
	else
		printf("ok %d - open(\"%s\", %s) succeeded\n",
		    testnum++, path, omodetext);
	flags1 = fcntl(fd, F_GETFL);
	if (flags1 == -1)
		printf("not ok %d - fcntl(F_GETFL) failed\n", testnum++);
	else if ((flags1 & CORRECT_O_ACCMODE) == omode)
		printf("ok %d - fcntl(F_GETFL) gave correct result\n",
		    testnum++);
	else
		printf("not ok %d - fcntl(F_GETFL) gave incorrect result "
		    "(%#x & %#x != %#x)\n",
		    testnum++, flags1, CORRECT_O_ACCMODE, omode);
	if (fcntl(fd, F_SETFL, flags1) == -1)
		printf("not ok %d - fcntl(F_SETFL) same flags failed\n",
		    testnum++);
	else
		printf("ok %d - fcntl(F_SETFL) same flags succeeded\n",
		    testnum++);
	flags2 = fcntl(fd, F_GETFL);
	if (flags2 == -1)
		printf("not ok %d - fcntl(F_GETFL) failed\n", testnum++);
	else if (flags2 == flags1)
		printf("ok %d - fcntl(F_GETFL) gave same result\n",
		    testnum++);
	else
		printf("not ok %d - fcntl(F_SETFL) caused fcntl(F_GETFL) to "
		    "change from %#x to %#x\n",
		    testnum++, flags1, flags2);
	if (fcntl(fd, F_SETFL, flags2 | O_NONBLOCK) == -1)
		printf("not ok %d - fcntl(F_SETFL) O_NONBLOCK failed\n",
		    testnum++);
	else
		printf("ok %d - fcntl(F_SETFL) O_NONBLOCK succeeded\n",
		    testnum++);
	flags3 = fcntl(fd, F_GETFL);
	if (flags3 == -1)
		printf("not ok %d - fcntl(F_GETFL) failed\n", testnum++);
	else if (flags3 == (flags2 | O_NONBLOCK))
		printf("ok %d - fcntl(F_GETFL) gave expected result\n",
		    testnum++);
	else
		printf("not ok %d - fcntl(F_SETFL) gave unexpected result "
		    "(%#x != %#x)\n",
		    testnum++, flags3, flags2 | O_NONBLOCK);
	(void)close(fd);
}