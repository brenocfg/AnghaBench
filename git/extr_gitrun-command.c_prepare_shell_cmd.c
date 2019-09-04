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
struct argv_array {char const** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 char const* SHELL_PATH ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushv (struct argv_array*,char const**) ; 
 scalar_t__ strcspn (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char **prepare_shell_cmd(struct argv_array *out, const char **argv)
{
	if (!argv[0])
		BUG("shell command is empty");

	if (strcspn(argv[0], "|&;<>()$`\\\"' \t\n*?[#~=%") != strlen(argv[0])) {
#ifndef GIT_WINDOWS_NATIVE
		argv_array_push(out, SHELL_PATH);
#else
		argv_array_push(out, "sh");
#endif
		argv_array_push(out, "-c");

		/*
		 * If we have no extra arguments, we do not even need to
		 * bother with the "$@" magic.
		 */
		if (!argv[1])
			argv_array_push(out, argv[0]);
		else
			argv_array_pushf(out, "%s \"$@\"", argv[0]);
	}

	argv_array_pushv(out, argv);
	return out->argv;
}