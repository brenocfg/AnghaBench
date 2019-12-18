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
 int MAXNUM ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ isblank (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  pfract (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char*) ; 
 int unit (int,char*) ; 

__attribute__((used)) static void
convert(char *line)
{
	int flen, len, rval;
	char *p, *fraction;

	flen = 0;
	fraction = NULL;
	for (p = line; *p != '\0' && *p != '\n'; ++p) {
		if (isblank(*p)) {
			if (p == line) {
				++line;
				continue;
			}
			goto badnum;
		}
		if (isdigit(*p))
			continue;
		switch (*p) {
		case '.':
			if (fraction != NULL)
				goto badnum;
			fraction = p + 1;
			*p = '\0';
			break;
		case '-':
			if (p == line)
				break;
			/* FALLTHROUGH */
		default:
badnum:			errx(1, "illegal number: %s", line);
			break;
		}
	}
	*p = '\0';

	if ((len = strlen(line)) > MAXNUM ||
	    (fraction != NULL && ((flen = strlen(fraction)) > MAXNUM)))
		errx(1, "number too large, max %d digits.", MAXNUM);

	if (*line == '-') {
		(void)printf("minus%s", lflag ? " " : "\n");
		++line;
		--len;
	}

	rval = len > 0 ? unit(len, line) : 0;
	if (fraction != NULL && flen != 0)
		for (p = fraction; *p != '\0'; ++p)
			if (*p != '0') {
				if (rval)
					(void)printf("%sand%s",
					    lflag ? " " : "",
					    lflag ? " " : "\n");
				if (unit(flen, fraction)) {
					if (lflag)
						(void)printf(" ");
					pfract(flen);
					rval = 1;
				}
				break;
			}
	if (!rval)
		(void)printf("zero%s", lflag ? "" : ".\n");
	if (lflag)
		(void)printf("\n");
}