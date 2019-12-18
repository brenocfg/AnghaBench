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
typedef  char* ccharp ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
colonify(ccharp *cpp)
{
	size_t s;
	char *cp;
	int i;

	if (cpp == NULL)
		return (0);

	for (s = 0, i = 0; cpp[i] != NULL; i++)
		s += strlen(cpp[i]) + 1;
	if ((cp = malloc(s + 1)) == NULL)
		abort();
	for (i = 0, *cp = '\0'; cpp[i] != NULL; i++) {
		strcat(cp, cpp[i]);
		strcat(cp, ":");
	}
	cp[s - 1] = '\0';		/* eliminate last colon */

	return (cp);
}