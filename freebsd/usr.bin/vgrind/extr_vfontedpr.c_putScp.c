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
 scalar_t__ ALTERNATE ; 
 int BUFSIZ ; 
 size_t PNAMELEN ; 
 size_t PSMAX ; 
 scalar_t__ STANDARD ; 
 int _escaped ; 
 scalar_t__ blklevel ; 
 scalar_t__ comtype ; 
 char* expmatch (char*,int /*<<< orphan*/ ,char*) ; 
 int inchr ; 
 int incomm ; 
 int instr ; 
 scalar_t__ isproc (char*) ; 
 int /*<<< orphan*/  l_acmbeg ; 
 int /*<<< orphan*/  l_acmend ; 
 int /*<<< orphan*/  l_blkbeg ; 
 int /*<<< orphan*/  l_blkend ; 
 int /*<<< orphan*/  l_chrbeg ; 
 int /*<<< orphan*/  l_chrend ; 
 int /*<<< orphan*/  l_combeg ; 
 int /*<<< orphan*/  l_comend ; 
 int /*<<< orphan*/  l_nocom ; 
 int /*<<< orphan*/  l_strbeg ; 
 int /*<<< orphan*/  l_strend ; 
 scalar_t__ nokeyw ; 
 scalar_t__* plstack ; 
 char* pname ; 
 int prccont ; 
 int /*<<< orphan*/  ps (char*) ; 
 size_t psptr ; 
 char** pstack ; 
 int /*<<< orphan*/  putKcp (char*,char*,int) ; 
 char* s_start ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void
putScp(char *os)
{
    register char *s = os;		/* pointer to unmatched string */
    char dummy[BUFSIZ];			/* dummy to be used by expmatch */
    char *comptr;			/* end of a comment delimiter */
    char *acmptr;			/* end of a comment delimiter */
    char *strptr;			/* end of a string delimiter */
    char *chrptr;			/* end of a character const delimiter */
    char *blksptr;			/* end of a lexical block start */
    char *blkeptr;			/* end of a lexical block end */
    char *nocomptr;			/* end of a non-comment delimiter */

    s_start = os;			/* remember the start for expmatch */
    _escaped = false;
    if (nokeyw || incomm || instr)
	goto skip;
    if (isproc(s)) {
	ps("'FN ");
	ps(pname);
        ps("\n");
	if (psptr < PSMAX) {
	    ++psptr;
	    strncpy (pstack[psptr], pname, PNAMELEN);
	    pstack[psptr][PNAMELEN] = '\0';
	    plstack[psptr] = blklevel;
	}
    }
skip:
    do {
	/* check for string, comment, blockstart, etc */
	if (!incomm && !instr && !inchr) {

	    blkeptr = expmatch(s, l_blkend, dummy);
	    blksptr = expmatch(s, l_blkbeg, dummy);
	    comptr = expmatch(s, l_combeg, dummy);
	    acmptr = expmatch(s, l_acmbeg, dummy);
	    strptr = expmatch(s, l_strbeg, dummy);
	    chrptr = expmatch(s, l_chrbeg, dummy);
	    nocomptr = expmatch (s, l_nocom, dummy);

	    /* start of non-comment? */
	    if (nocomptr != NULL)
		if ((nocomptr <= comptr || comptr == NULL)
		  && (nocomptr <= acmptr || acmptr == NULL)) {
		    /* continue after non-comment */
		    putKcp (s, nocomptr-1, false);
		    s = nocomptr;
		    continue;
		}

	    /* start of a comment? */
	    if (comptr != NULL)
		if ((comptr < strptr || strptr == NULL)
		  && (comptr < acmptr || acmptr == NULL)
		  && (comptr < chrptr || chrptr == NULL)
		  && (comptr < blksptr || blksptr == NULL)
		  && (comptr < blkeptr || blkeptr == NULL)) {
		    putKcp(s, comptr-1, false);
		    s = comptr;
		    incomm = true;
		    comtype = STANDARD;
		    if (s != os)
			ps("\\c");
		    ps("\\c\n'+C\n");
		    continue;
		}

	    /* start of a comment? */
	    if (acmptr != NULL)
		if ((acmptr < strptr || strptr == NULL)
		  && (acmptr < chrptr || chrptr == NULL)
		  && (acmptr < blksptr || blksptr == NULL)
		  && (acmptr < blkeptr || blkeptr == NULL)) {
		    putKcp(s, acmptr-1, false);
		    s = acmptr;
		    incomm = true;
		    comtype = ALTERNATE;
		    if (s != os)
			ps("\\c");
		    ps("\\c\n'+C\n");
		    continue;
		}

	    /* start of a string? */
	    if (strptr != NULL)
		if ((strptr < chrptr || chrptr == NULL)
		  && (strptr < blksptr || blksptr == NULL)
		  && (strptr < blkeptr || blkeptr == NULL)) {
		    putKcp(s, strptr-1, false);
		    s = strptr;
		    instr = true;
		    continue;
		}

	    /* start of a character string? */
	    if (chrptr != NULL)
		if ((chrptr < blksptr || blksptr == NULL)
		  && (chrptr < blkeptr || blkeptr == NULL)) {
		    putKcp(s, chrptr-1, false);
		    s = chrptr;
		    inchr = true;
		    continue;
		}

	    /* end of a lexical block */
	    if (blkeptr != NULL) {
		if (blkeptr < blksptr || blksptr == NULL) {
		    putKcp(s, blkeptr - 1, false);
		    s = blkeptr;
		    if (blklevel > 0 /* sanity */)
			    blklevel--;
		    if (psptr >= 0 && plstack[psptr] >= blklevel) {

			/* end of current procedure */
			if (s != os)
			    ps("\\c");
			ps("\\c\n'-F\n");
			blklevel = plstack[psptr];

			/* see if we should print the last proc name */
			if (--psptr >= 0)
			    prccont = true;
			else
			    psptr = -1;
		    }
		    continue;
		}
	    }

	    /* start of a lexical block */
	    if (blksptr != NULL) {
		putKcp(s, blksptr - 1, false);
		s = blksptr;
		blklevel++;
		continue;
	    }

	/* check for end of comment */
	} else if (incomm) {
	    comptr = expmatch(s, l_comend, dummy);
	    acmptr = expmatch(s, l_acmend, dummy);
	    if (((comtype == STANDARD) && (comptr != NULL)) ||
	        ((comtype == ALTERNATE) && (acmptr != NULL))) {
		if (comtype == STANDARD) {
		    putKcp(s, comptr-1, true);
		    s = comptr;
		} else {
		    putKcp(s, acmptr-1, true);
		    s = acmptr;
		}
		incomm = false;
		ps("\\c\n'-C\n");
		continue;
	    } else {
		putKcp(s, s + strlen(s) -1, true);
		s = s + strlen(s);
		continue;
	    }

	/* check for end of string */
	} else if (instr) {
	    if ((strptr = expmatch(s, l_strend, dummy)) != NULL) {
		putKcp(s, strptr-1, true);
		s = strptr;
		instr = false;
		continue;
	    } else {
		putKcp(s, s+strlen(s)-1, true);
		s = s + strlen(s);
		continue;
	    }

	/* check for end of character string */
	} else if (inchr) {
	    if ((chrptr = expmatch(s, l_chrend, dummy)) != NULL) {
		putKcp(s, chrptr-1, true);
		s = chrptr;
		inchr = false;
		continue;
	    } else {
		putKcp(s, s+strlen(s)-1, true);
		s = s + strlen(s);
		continue;
	    }
	}

	/* print out the line */
	putKcp(s, s + strlen(s) -1, false);
	s = s + strlen(s);
    } while (*s);
}