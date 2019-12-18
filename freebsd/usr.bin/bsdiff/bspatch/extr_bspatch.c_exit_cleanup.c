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
 int dirfd ; 
 int /*<<< orphan*/ * newfile ; 
 scalar_t__ unlinkat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
exit_cleanup(void)
{

	if (dirfd != -1 && newfile != NULL)
		if (unlinkat(dirfd, newfile, 0))
			warn("unlinkat");
}