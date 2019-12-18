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
 int /*<<< orphan*/  fconfig ; 
 int getc (int /*<<< orphan*/ ) ; 
 char* nextline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
skip(char **cpp)
{
	char *cp = *cpp;
	char *start;
	char quote = '\0';

again:
	while (*cp == ' ' || *cp == '\t')
		cp++;
	if (*cp == '\0') {
		int c;

		c = getc(fconfig);
		(void) ungetc(c, fconfig);
		if (c == ' ' || c == '\t')
			if ((cp = nextline(fconfig)))
				goto again;
		*cpp = (char *)0;
		return ((char *)0);
	}
	if (*cp == '"' || *cp == '\'')
		quote = *cp++;
	start = cp;
	if (quote)
		while (*cp && *cp != quote)
			cp++;
	else
		while (*cp && *cp != ' ' && *cp != '\t')
			cp++;
	if (*cp != '\0')
		*cp++ = '\0';
	*cpp = cp;
	return (start);
}