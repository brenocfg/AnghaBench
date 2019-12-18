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
 int LINESIZE ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isprint (unsigned char) ; 
 int readline (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

int
gethfield(FILE *f, char linebuf[], int rem, char **colon)
{
	char line2[LINESIZE];
	char *cp, *cp2;
	int c;

	for (;;) {
		if (--rem < 0)
			return (-1);
		if ((c = readline(f, linebuf, LINESIZE)) <= 0)
			return (-1);
		for (cp = linebuf; isprint((unsigned char)*cp) && *cp != ' ' && *cp != ':';
		    cp++)
			;
		if (*cp != ':' || cp == linebuf)
			continue;
		/*
		 * I guess we got a headline.
		 * Handle wraparounding
		 */
		*colon = cp;
		cp = linebuf + c;
		for (;;) {
			while (--cp >= linebuf && (*cp == ' ' || *cp == '\t'))
				;
			cp++;
			if (rem <= 0)
				break;
			ungetc(c = getc(f), f);
			if (c != ' ' && c != '\t')
				break;
			if ((c = readline(f, line2, LINESIZE)) < 0)
				break;
			rem--;
			for (cp2 = line2; *cp2 == ' ' || *cp2 == '\t'; cp2++)
				;
			c -= cp2 - line2;
			if (cp + c >= linebuf + LINESIZE - 2)
				break;
			*cp++ = ' ';
			bcopy(cp2, cp, c);
			cp += c;
		}
		*cp = 0;
		return (rem);
	}
	/* NOTREACHED */
}