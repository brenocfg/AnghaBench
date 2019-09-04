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
 int /*<<< orphan*/  svndump_deinit () ; 
 scalar_t__ svndump_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svndump_read (char*,char*,char*) ; 
 int /*<<< orphan*/  svndump_reset () ; 

int main(int argc, char **argv)
{
	if (svndump_init(NULL))
		return 1;
	svndump_read((argc > 1) ? argv[1] : NULL, "refs/heads/master",
			"refs/notes/svn/revs");
	svndump_deinit();
	svndump_reset();
	return 0;
}