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
 int /*<<< orphan*/  add_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curfilename ; 
 int goterror ; 
 scalar_t__ is_dir (char*) ; 
 int /*<<< orphan*/  linenum ; 
 int /*<<< orphan*/  srcdirs ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
add_srcdirs(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++) {
		if (is_dir(argv[i]))
			add_string(&srcdirs, argv[i]);
		else {
			warnx("%s:%d: `%s' is not a directory, skipping it",
			    curfilename, linenum, argv[i]);
			goterror = 1;
		}
	}
}