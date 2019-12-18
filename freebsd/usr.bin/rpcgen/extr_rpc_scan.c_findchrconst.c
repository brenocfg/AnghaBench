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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
findchrconst(char **str, const char **val)
{
	char *p;
	char *tmp;
	int size;

	p = *str;
	do {
		p++;
	} while (*p && *p != '\'');
	if (*p == 0) {
		error("unterminated string constant");
	}
	p++;
	size = p - *str + 1;
	if (size != 4) {
		error("empty char string");
	}
	tmp = xmalloc(size);
	(void) strlcpy(tmp, *str, size);
	*val = tmp;
	*str = p;
}