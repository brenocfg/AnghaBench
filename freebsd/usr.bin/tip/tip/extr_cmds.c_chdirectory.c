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
typedef  int /*<<< orphan*/  dirname ;

/* Variables and functions */
 int /*<<< orphan*/  HOME ; 
 int PATH_MAX ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ prompt (char*,char*,int) ; 
 scalar_t__ stoprompt ; 
 char* value (int /*<<< orphan*/ ) ; 

void
chdirectory(int c)
{
	char dirname[PATH_MAX];
	char *cp = dirname;

	if (prompt("[cd] ", dirname, sizeof(dirname))) {
		if (stoprompt)
			return;
		cp = value(HOME);
	}
	if (chdir(cp) < 0)
		printf("%s: bad directory\r\n", cp);
	printf("!\r\n");
}