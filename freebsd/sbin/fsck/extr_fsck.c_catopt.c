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
 char* erealloc (char*,size_t) ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
catopt(char **sp, const char *o)
{
	char *s;
	size_t i, j;

	s = *sp;
	if (s) {
		i = strlen(s);
		j = i + 1 + strlen(o) + 1;
		s = erealloc(s, j);
		(void)snprintf(s + i, j, ",%s", o);
	} else
		s = estrdup(o);
	*sp = s;
}