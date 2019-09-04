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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int dup (int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sanitize_stdfds(void)
{
	int fd = open("/dev/null", O_RDWR, 0);
	while (fd != -1 && fd < 2)
		fd = dup(fd);
	if (fd == -1)
		die_errno(_("open /dev/null or dup failed"));
	if (fd > 2)
		close(fd);
}