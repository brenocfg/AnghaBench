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
typedef  int Char ;

/* Variables and functions */
 int ERR_MISSING ; 
 int ERR_NAME ; 
 int* Strend (int const*) ; 
 int TRIM ; 
 int /*<<< orphan*/  Tolower (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  globcharcoll (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int,char) ; 

int
t_pmatch(const Char *string, const Char *pattern, const Char **estr, int cs)
{
    Char stringc, patternc, rangec;
    int     match, negate_range;
    const Char *pestr, *nstring;

    for (nstring = string;; string = nstring) {
	stringc = *nstring++ & TRIM;
	patternc = *pattern++ & TRIM;
	switch (patternc) {
	case '\0':
	    *estr = string;
	    return (stringc == '\0' ? 2 : 1);
	case '?':
	    if (stringc == 0)
		return (0);
	    break;
	case '*':
	    if (!*pattern) {
		*estr = Strend(string);
		return (2);
	    }
	    pestr = NULL;

	    for (;;) {
		switch(t_pmatch(string, pattern, estr, cs)) {
		case 0:
		    break;
		case 1:
		    pestr = *estr;/*FIXME: does not guarantee longest match */
		    break;
		case 2:
		    return 2;
		default:
		    abort();	/* Cannot happen */
		}
		stringc = *string++ & TRIM;
		if (!stringc)
		    break;
	    }

	    if (pestr) {
		*estr = pestr;
		return 1;
	    }
	    else
		return 0;

	case '[':
	    match = 0;
	    if ((negate_range = (*pattern == '^')) != 0)
		pattern++;
	    while ((rangec = *pattern++ & TRIM) != '\0') {
		if (rangec == ']')
		    break;
		if (match)
		    continue;
		if (*pattern == '-' && pattern[1] != ']') {
		    Char rangec2;
		    pattern++;
		    rangec2 = *pattern++ & TRIM;
		    match = (globcharcoll(stringc, rangec2, 0) <= 0 &&
			globcharcoll(rangec, stringc, 0) <= 0);
		}
		else 
		    match = (stringc == rangec);
	    }
	    if (rangec == '\0')
		stderror(ERR_NAME | ERR_MISSING, ']');
	    if ((!match) && (stringc == '\0'))
		return (0);
	    if (match == negate_range)
		return (0);
	    break;
	default:
	    if (cs ? patternc  != stringc
		: Tolower(patternc) != Tolower(stringc))
		return (0);
	    break;
	}
    }
}