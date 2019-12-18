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
 char** environ ; 
 char** malloc (int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static void
blank_env(const char *var)
{
	char **newenviron;
	int n, varlen;

	if (environ == NULL)
		return;

	for (n = 0; environ[n] != NULL; n++)
		;
	newenviron = malloc(sizeof(char *) * (n + 1));
	varlen = strlen(var);
	for (; n >= 0; n--) {
		newenviron[n] = environ[n];
		if (newenviron[n] != NULL &&
		    strncmp(newenviron[n], var, varlen) == 0 &&
		    newenviron[n][varlen] == '=')
			newenviron[n] += strlen(newenviron[n]);
	}
	environ = newenviron;
}