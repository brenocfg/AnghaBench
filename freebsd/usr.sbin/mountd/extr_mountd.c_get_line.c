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
 int /*<<< orphan*/  exp_file ; 
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 char* line ; 
 size_t linesize ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  out_of_mem () ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static int
get_line(void)
{
	char *p, *cp;
	size_t len;
	int totlen, cont_line;

	/*
	 * Loop around ignoring blank lines and getting all continuation lines.
	 */
	p = line;
	totlen = 0;
	do {
		if ((p = fgetln(exp_file, &len)) == NULL)
			return (0);
		cp = p + len - 1;
		cont_line = 0;
		while (cp >= p &&
		    (*cp == ' ' || *cp == '\t' || *cp == '\n' || *cp == '\\')) {
			if (*cp == '\\')
				cont_line = 1;
			cp--;
			len--;
		}
		if (cont_line) {
			*++cp = ' ';
			len++;
		}
		if (linesize < len + totlen + 1) {
			linesize = len + totlen + 1;
			line = realloc(line, linesize);
			if (line == NULL)
				out_of_mem();
		}
		memcpy(line + totlen, p, len);
		totlen += len;
		line[totlen] = '\0';
	} while (totlen == 0 || cont_line);
	return (1);
}