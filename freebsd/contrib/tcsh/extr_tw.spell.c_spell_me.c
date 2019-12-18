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
struct Strbuf {char* s; size_t len; } ;
typedef  int /*<<< orphan*/  eChar ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  SPELL ; 
 scalar_t__ StrQcmp (char*,char*) ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,char*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char const) ; 
 int /*<<< orphan*/  Strbuf_cleanup ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int TW_COMMAND ; 
 int /*<<< orphan*/  cleanup_ignore (struct Strbuf*) ; 
 int /*<<< orphan*/  cleanup_push (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct Strbuf*) ; 
 int t_search (struct Strbuf*,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

int
spell_me(struct Strbuf *oldname, int looking, Char *pat, eChar suf)
{
    struct Strbuf guess = Strbuf_INIT, newname = Strbuf_INIT;
    const Char *old = oldname->s;
    size_t ws;
    int    foundslash = 0;
    int     retval;

    cleanup_push(&guess, Strbuf_cleanup);
    cleanup_push(&newname, Strbuf_cleanup);
    for (;;) {
	while (*old == '/') {	/* skip '/' */
	    Strbuf_append1(&newname, *old++);
	    foundslash = 1;
	}
	/* do not try to correct spelling of single letter words */
	if (*old != '\0' && old[1] == '\0')
	    Strbuf_append1(&newname, *old++);
	Strbuf_terminate(&newname);
	if (*old == '\0') {
	    retval = (StrQcmp(oldname->s, newname.s) != 0);
	    cleanup_ignore(&newname);
	    xfree(oldname->s);
	    *oldname = newname; /* shove it back. */
	    cleanup_until(&guess);
	    return retval;
	}
	guess.len = 0;		/* start at beginning of buf */
	Strbuf_append(&guess, newname.s); /* add current dir if any */
	ws = guess.len;
	for (; *old != '/' && *old != '\0'; old++)/* add current file name */
	    Strbuf_append1(&guess, *old);
	Strbuf_terminate(&guess);

	/*
	 * Don't tell t_search we're looking for cmd if no '/' in the name so
	 * far but there are later - or it will look for *all* commands
	 */
	/* (*should* say "looking for directory" whenever '/' is next...) */
	retval = t_search(&guess, SPELL,
			  looking == TW_COMMAND && (foundslash || *old != '/') ?
			  TW_COMMAND : looking, 1, pat, suf);
	if (retval >= 4 || retval < 0) {
	    cleanup_until(&guess);
	    return -1;		/* hopeless */
	}
	Strbuf_append(&newname, guess.s + ws);
    }
/*NOTREACHED*/
#ifdef notdef
    return (0);			/* lint on the vax under mtXinu complains! */
#endif
}