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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MAXID ; 
 int bol ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lineno ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 int token (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
skipto(FILE *fd, const char *what)
{
	char id[MAXID];
	int c;

	for (;;) {
		c = getc(fd);
		if (c == EOF)
			goto bad;
		if (c == '.' && bol) {		/* .directive */
			if (token(fd, id, MAXID, ".directive") == EOF)
				goto bad;
			if (strcasecmp(id, what) == 0)
				break;
			continue;
		}
		if (c == '\\') {		/* escape next character */
			c = getc(fd);
			if (c == EOF)
				goto bad;
		}
		bol = (c == '\n');
		if (bol)
			lineno++;
	}
	return 0;
bad:
	warnx("EOF with no matching .%s", what);
	return EOF;
}