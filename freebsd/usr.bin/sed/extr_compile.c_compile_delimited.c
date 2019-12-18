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
 char* compile_ccl (char**,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname ; 
 int /*<<< orphan*/  linenum ; 

__attribute__((used)) static char *
compile_delimited(char *p, char *d, int is_tr)
{
	char c;

	c = *p++;
	if (c == '\0')
		return (NULL);
	else if (c == '\\')
		errx(1, "%lu: %s: \\ can not be used as a string delimiter",
				linenum, fname);
	else if (c == '\n')
		errx(1, "%lu: %s: newline can not be used as a string delimiter",
				linenum, fname);
	while (*p) {
		if (*p == '[' && *p != c) {
			if ((d = compile_ccl(&p, d)) == NULL)
				errx(1, "%lu: %s: unbalanced brackets ([])", linenum, fname);
			continue;
		} else if (*p == '\\' && p[1] == '[') {
			*d++ = *p++;
		} else if (*p == '\\' && p[1] == c)
			p++;
		else if (*p == '\\' && p[1] == 'n') {
			*d++ = '\n';
			p += 2;
			continue;
		} else if (*p == '\\' && p[1] == '\\') {
			if (is_tr)
				p++;
			else
				*d++ = *p++;
		} else if (*p == c) {
			*d = '\0';
			return (p + 1);
		}
		*d++ = *p++;
	}
	return (NULL);
}