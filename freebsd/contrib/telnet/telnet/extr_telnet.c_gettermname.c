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
 char* env_getvalue (char*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 char** mklist (int /*<<< orphan*/ ,char*) ; 
 char* name_unknown ; 
 scalar_t__ resettermname ; 
 scalar_t__ setupterm (char*,int,int*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  termbuf ; 
 char const** unknown ; 
 int /*<<< orphan*/  upcase (char*) ; 

__attribute__((used)) static const char *
gettermname(void)
{
	char *tname;
	static const char **tnamep = 0;
	static const char **next;
	int err;

	if (resettermname) {
		resettermname = 0;
		if (tnamep && tnamep != unknown)
			free(tnamep);
		if ((tname = env_getvalue("TERM")) &&
				(setupterm(tname, 1, &err) == 0)) {
			tnamep = mklist(termbuf, tname);
		} else {
			if (tname && (strlen(tname) <= 40)) {
				unknown[0] = tname;
				upcase(tname);
			} else
				unknown[0] = name_unknown;
			tnamep = unknown;
		}
		next = tnamep;
	}
	if (*next == 0)
		next = tnamep;
	return(*next++);
}