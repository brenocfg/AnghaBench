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
 scalar_t__ EINTR ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_CANTCREAT ; 
 int O_EXLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int open (char const*,int,int) ; 

__attribute__((used)) static void
wait_for_lock(const char *name)
{
	int fd;

	if ((fd = open(name, O_RDONLY|O_EXLOCK, 0666)) == -1) {
		if (errno == ENOENT || errno == EINTR)
			return;
		err(EX_CANTCREAT, "cannot open %s", name);
	}
	close(fd);
}