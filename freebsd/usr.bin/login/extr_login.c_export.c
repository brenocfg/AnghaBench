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
 int /*<<< orphan*/  setenv (char const*,char*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
export(const char *s)
{
	static const char *noexport[] = {
		"SHELL", "HOME", "LOGNAME", "MAIL", "CDPATH",
		"IFS", "PATH", NULL
	};
	char *p;
	const char **pp;
	size_t n;

	if (strlen(s) > 1024 || (p = strchr(s, '=')) == NULL)
		return (0);
	if (strncmp(s, "LD_", 3) == 0)
		return (0);
	for (pp = noexport; *pp != NULL; pp++) {
		n = strlen(*pp);
		if (s[n] == '=' && strncmp(s, *pp, n) == 0)
			return (0);
	}
	*p = '\0';
	(void)setenv(s, p + 1, 1);
	*p = '=';
	return (1);
}