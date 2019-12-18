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
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  filebase ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void *
writer(void *a)
{
	int *fd = (int *)a;

	while (TRUE) {
		(void) close (*fd);
		*fd = open(filebase, O_APPEND | O_RDWR | O_CREAT, 0644);
		if (*fd < 0)
			perror("refreshing file");
		(void) write(*fd, "test\n", 5);
	}

	return (NULL);
}