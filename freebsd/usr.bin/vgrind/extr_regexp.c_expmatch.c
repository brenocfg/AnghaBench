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
 char ALT ; 
#define  META 130 
 char* MNEXT (char*) ; 
 int /*<<< orphan*/  MSYM (char*) ; 
 char* ONEXT (char*) ; 
#define  OPER 129 
 char OPT ; 
 char* OPTR (char*) ; 
 int /*<<< orphan*/  OSYM (char*) ; 
 int /*<<< orphan*/  SCNT (char*) ; 
 char* SNEXT (char*) ; 
 int /*<<< orphan*/  SSTR (char*) ; 
#define  STR 128 
 int /*<<< orphan*/  STRNCMP (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _escaped ; 
 int /*<<< orphan*/  isalnum (char) ; 
 char* s_start ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

char *
expmatch (register char *s, register char *re, register char *mstring)
{
    register char *cs;		/* the current symbol */
    register char *ptr,*s1;	/* temporary pointer */
    bool matched;	/* a temporary bool */

    /* initial conditions */
    if (re == NULL)
	return (NULL);
    cs = re;
    matched = false;

    /* loop till expression string is exhausted (or at least pretty tired) */
    while (*cs) {
	switch (*cs & (OPER | STR | META)) {

	/* try to match a string */
	case STR:
	    matched = !STRNCMP (s, SSTR(cs), SCNT(cs));
	    if (matched) {

		/* hoorah it matches */
		s += SCNT(cs);
		cs = SNEXT(cs);
	    } else if (*cs & ALT) {

		/* alternation, skip to next expression */
		cs = SNEXT(cs);
	    } else if (*cs & OPT) {

		/* the match is optional */
		cs = SNEXT(cs);
		matched = 1;		/* indicate a successful match */
	    } else {

		/* no match, error return */
		return (NULL);
	    }
	    break;

	/* an operator, do something fancy */
	case OPER:
	    switch (OSYM(cs)) {

	    /* this is an alternation */
	    case '|':
		if (matched)

		    /* last thing in the alternation was a match, skip ahead */
		    cs = OPTR(cs);
		else

		    /* no match, keep trying */
		    cs = ONEXT(cs);
		break;

	    /* this is a grouping, recurse */
	    case '(':
		ptr = expmatch(s, ONEXT(cs), mstring);
		if (ptr != NULL) {

		    /* the subexpression matched */
		    matched = 1;
		    s = ptr;
		} else if (*cs & ALT) {

		    /* alternation, skip to next expression */
		    matched = 0;
		} else if (*cs & OPT) {

		    /* the match is optional */
		    matched = 1;	/* indicate a successful match */
		} else {

		    /* no match, error return */
		    return (NULL);
		}
		cs = OPTR(cs);
		break;
	    }
	    break;

	/* try to match a metasymbol */
	case META:
	    switch (MSYM(cs)) {

	    /* try to match anything and remember what was matched */
	    case 'p':
		/*
		 *  This is really the same as trying the match the
		 *  remaining parts of the expression to any subset
		 *  of the string.
		 */
		s1 = s;
		do {
		    ptr = expmatch(s1, MNEXT(cs), mstring);
		    if (ptr != NULL && s1 != s) {

			/* we have a match, remember the match */
			strncpy (mstring, s, s1 - s);
			mstring[s1 - s] = '\0';
			return (ptr);
		    } else if (ptr != NULL && (*cs & OPT)) {

			/* it was aoptional so no match is ok */
			return (ptr);
		    } else if (ptr != NULL) {

			/* not optional and we still matched */
			return (NULL);
		    }
		    if (!(isalnum(*s1) || *s1 == '_' ||
			  /* C++ destructor */
			  *s1 == '~' ||
			  /* C++ scope operator */
			  (strlen(s1) > 1 && *s1 == ':' && s1[1] == ':' &&
			   (s1++, true))))
			return (NULL);
		    if (*s1 == '\\')
			_escaped = _escaped ? false : true;
		    else
			_escaped = false;
		} while (*s1++);
		return (NULL);

	    /* try to match anything */
	    case 'a':
		/*
		 *  This is really the same as trying the match the
		 *  remaining parts of the expression to any subset
		 *  of the string.
		 */
		s1 = s;
		do {
		    ptr = expmatch(s1, MNEXT(cs), mstring);
		    if (ptr != NULL && s1 != s) {

			/* we have a match */
			return (ptr);
		    } else if (ptr != NULL && (*cs & OPT)) {

			/* it was aoptional so no match is ok */
			return (ptr);
		    } else if (ptr != NULL) {

			/* not optional and we still matched */
			return (NULL);
		    }
		    if (*s1 == '\\')
			_escaped = _escaped ? false : true;
		    else
			_escaped = false;
		} while (*s1++);
		return (NULL);

	    /* fail if we are currently _escaped */
	    case 'e':
		if (_escaped)
		    return(NULL);
		cs = MNEXT(cs);
		break;

	    /* match any number of tabs and spaces */
	    case 'd':
		ptr = s;
		while (*s == ' ' || *s == '\t')
		    s++;
		if (s != ptr || s == s_start) {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*s == '\n' || *s == '\0') {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NULL);
		break;

	    /* check for end of line */
	    case '$':
		if (*s == '\0' || *s == '\n') {

		    /* match, be happy */
		    s++;
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NULL);
		break;

	    /* check for start of line */
	    case '^':
		if (s == s_start) {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NULL);
		break;

	    /* end of a subexpression, return success */
	    case ')':
		return (s);
	    }
	    break;
	}
    }
    return (s);
}