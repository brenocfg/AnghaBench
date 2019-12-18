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
struct passwd {int /*<<< orphan*/  pw_uid; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_two () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int fork () ; 
 struct passwd* getpwnam (char const*) ; 
 int setuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
child_one(void)
{
	pid_t pid;
	struct passwd *pwd;
	const char *nam = "nobody";

	pwd = getpwnam(nam);
	if (pwd == NULL)
		err(EXIT_FAILURE, "getpwnam(\"%s\")", nam);

	if ((setuid(pwd->pw_uid)) == -1)
		err(EXIT_FAILURE, "setuid(%d)", pwd->pw_uid);

	pid = fork();
	if (pid == -1)
		err(EXIT_FAILURE, "fork()");

	if (pid == 0)
		child_two();

	_exit(EXIT_SUCCESS);
}