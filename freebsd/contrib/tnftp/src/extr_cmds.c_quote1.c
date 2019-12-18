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
 int BUFSIZ ; 
 scalar_t__ PRELIM ; 
 scalar_t__ command (char*,char*) ; 
 int dirchange ; 
 scalar_t__ getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void
quote1(const char *initial, int argc, char *argv[])
{
	int i;
	char buf[BUFSIZ];		/* must be >= sizeof(line) */

	(void)strlcpy(buf, initial, sizeof(buf));
	for (i = 1; i < argc; i++) {
		(void)strlcat(buf, argv[i], sizeof(buf));
		if (i < (argc - 1))
			(void)strlcat(buf, " ", sizeof(buf));
	}
	if (command("%s", buf) == PRELIM) {
		while (getreply(0) == PRELIM)
			continue;
	}
	dirchange = 1;
}