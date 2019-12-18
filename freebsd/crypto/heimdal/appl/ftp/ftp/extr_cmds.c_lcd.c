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
 int MaxPathLen ; 
 scalar_t__ chdir (char*) ; 
 int code ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  globulize (char**) ; 
 char* home ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

void
lcd(int argc, char **argv)
{
	char buf[MaxPathLen];

	if (argc < 2)
		argc++, argv[1] = home;
	if (argc != 2) {
		printf("usage: %s local-directory\n", argv[0]);
		code = -1;
		return;
	}
	if (!globulize(&argv[1])) {
		code = -1;
		return;
	}
	if (chdir(argv[1]) < 0) {
		warn("local: %s", argv[1]);
		code = -1;
		return;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("Local directory now %s\n", buf);
	else
		warnx("getwd: %s", buf);
	code = 0;
}