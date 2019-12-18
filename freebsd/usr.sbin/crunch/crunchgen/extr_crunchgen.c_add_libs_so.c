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
 scalar_t__ in_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  libs ; 
 int /*<<< orphan*/  libs_so ; 
 int /*<<< orphan*/  linenum ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
add_libs_so(int argc, char **argv)
{
	int i;

	for(i = 1; i < argc; i++) {
		add_string(&libs_so, argv[i]);
		if ( in_list(&libs, argv[i]) )
			warnx("%s:%d: "
				"library `%s' specified as static earlier",
				curfilename, linenum, argv[i]);
	}
}