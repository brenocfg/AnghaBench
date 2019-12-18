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
 char const* __progname ; 
 char** environ ; 

__attribute__((used)) static inline void
handle_argv(int argc, char *argv[], char **env)
{
	const char *s;

	if (environ == NULL)
		environ = env;
	if (argc > 0 && argv[0] != NULL) {
		__progname = argv[0];
		for (s = __progname; *s != '\0'; s++) {
			if (*s == '/')
				__progname = s + 1;
		}
	}
}