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
 int NUM_OPENS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

int
main(void)
{
	int i, max, fds[NUM_OPENS];
	char buf[512];

	for (i = 0; i < NUM_OPENS; i++)
		if ((fds[i] = open("/dev/null", O_RDONLY)) == -1)
			exit(0);	/* can't test */
	max = i - 1;

	/* should close last fd only */
	closefrom(fds[max]);
	if (close(fds[max]) != -1)
		fail("failed to close highest fd");

	/* make sure we can still use remaining descriptors */
	for (i = 0; i < max; i++)
		if (read(fds[i], buf, sizeof(buf)) == -1)
			fail("closed descriptors it should not have");

	/* should close all fds */
	closefrom(fds[0]);
	for (i = 0; i < NUM_OPENS; i++)
		if (close(fds[i]) != -1)
			fail("failed to close from lowest fd");
	return 0;
}