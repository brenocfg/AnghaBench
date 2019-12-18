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
typedef  int off_t ;
typedef  int /*<<< orphan*/  dbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int hashit (char*,int) ; 
 char* linebuf ; 
 int /*<<< orphan*/  octdigit (char) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static off_t
yankstr(char **cpp)
{
	char *cp = *cpp;
	int c, ch;
	char dbuf[BUFSIZ];
	char *dp = dbuf;
	char *tp;
	static char tmp[] = "b\bt\tr\rn\nf\f\\\\\"\"";

	while ((c = *cp++)) {
		if (dp == dbuf + sizeof(dbuf) - 3)
			errx(1, "message too long");
		switch (c) {

		case '"':
			cp++;
			goto out;

		case '\\':
			c = *cp++;
			if (c == 0)
				break;
			if (c == '\n') {
				if (fgets(linebuf, sizeof linebuf, stdin)
				    == NULL) {
					if (ferror(stdin))
						err(3, "x.c");
					return(-1);
				}
				cp = linebuf;
				continue;
			}
			for (tp = tmp; (ch = *tp++); tp++)
				if (c == ch) {
					c = *tp;
					goto gotc;
				}
			if (!octdigit(c)) {
				*dp++ = '\\';
				break;
			}
			c -= '0';
			if (!octdigit(*cp))
				break;
			c <<= 3, c += *cp++ - '0';
			if (!octdigit(*cp))
				break;
			c <<= 3, c += *cp++ - '0';
			break;
		}
gotc:
		*dp++ = c;
	}
out:
	*cpp = --cp;
	*dp = 0;
	return (hashit(dbuf, 1));
}