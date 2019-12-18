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
 int REG_BACKR ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_LARGE ; 
 int REG_NEWLINE ; 
 int REG_NOSPEC ; 
 int REG_NOSUB ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int REG_PEND ; 
 int REG_STARTEND ; 
 int REG_TRACE ; 
 int copts ; 
 int eopts ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

int
options(int type, char *s)
{
	char *p;
	int o = (type == 'c') ? copts : eopts;
	const char *legal = (type == 'c') ? "bisnmp" : "^$#tl";

	for (p = s; *p != '\0'; p++)
		if (strchr(legal, *p) != NULL)
			switch (*p) {
			case 'b':
				o &= ~REG_EXTENDED;
				break;
			case 'i':
				o |= REG_ICASE;
				break;
			case 's':
				o |= REG_NOSUB;
				break;
			case 'n':
				o |= REG_NEWLINE;
				break;
			case 'm':
				o &= ~REG_EXTENDED;
				o |= REG_NOSPEC;
				break;
			case 'p':
				o |= REG_PEND;
				break;
			case '^':
				o |= REG_NOTBOL;
				break;
			case '$':
				o |= REG_NOTEOL;
				break;
			case '#':
				o |= REG_STARTEND;
				break;
			case 't':	/* trace */
				o |= REG_TRACE;
				break;
			case 'l':	/* force long representation */
				o |= REG_LARGE;
				break;
			case 'r':	/* force backref use */
				o |= REG_BACKR;
				break;
			}
	return(o);
}