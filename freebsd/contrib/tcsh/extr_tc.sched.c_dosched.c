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
typedef  void* time_t ;
struct tm {int tm_hour; int tm_min; void* tm_sec; } ;
struct sched_event {scalar_t__ t_when; int /*<<< orphan*/  t_lex; struct sched_event* t_next; } ;
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 char* CGETS (int,int,char*) ; 
 int /*<<< orphan*/  ERR_NOSCHED ; 
 int /*<<< orphan*/  ERR_SCHEDCOM ; 
 int /*<<< orphan*/  ERR_SCHEDEV ; 
 int /*<<< orphan*/  ERR_SCHEDREL ; 
 int /*<<< orphan*/  ERR_SCHEDTIME ; 
 int /*<<< orphan*/  ERR_SCHEDUSAGE ; 
 int /*<<< orphan*/  FMT_SCHED ; 
 int /*<<< orphan*/  Isdigit (char) ; 
 char const* STRNULL ; 
 int /*<<< orphan*/  STRsched ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 char* blkexpand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (struct sched_event*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 struct tm* localtime (void**) ; 
 int /*<<< orphan*/  saveblk (char**) ; 
 struct sched_event* sched_ptr ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 char* str2short (char*) ; 
 int /*<<< orphan*/  time (void**) ; 
 char* tprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 char* varval (int /*<<< orphan*/ ) ; 
 struct sched_event* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree (struct sched_event*) ; 
 int /*<<< orphan*/  xputwchar (int /*<<< orphan*/ ) ; 

void
dosched(Char **v, struct command *c)
{
    struct sched_event *tp, **pp;
    time_t  cur_time;
    int     count, hours, minutes, dif_hour, dif_min;
    Char   *cp;
    int    relative;		/* time specified as +hh:mm */
    struct tm *ltp;

    USE(c);
/* This is a major kludge because of a gcc linker  */
/* Problem.  It may or may not be needed for you   */
#if defined(_MINIX) && !defined(_MINIX_VMD)
    char kludge[10];
    extern char *sprintf();
    sprintf(kludge, CGETS(24, 1, "kludge"));
#endif /* _MINIX && !_MINIX_VMD */

    v++;
    cp = *v++;
    if (cp == NULL) {
	const Char *fmt;
	if ((fmt = varval(STRsched)) == STRNULL)
	    fmt = str2short("%h\t%T\t%R\n");
	/* print list of scheduled events */
	for (count = 1, tp = sched_ptr; tp; count++, tp = tp->t_next) {
	    Char *buf, *str;

	    buf = blkexpand(tp->t_lex);
	    cleanup_push(buf, xfree);
	    str = tprintf(FMT_SCHED, fmt, short2str(buf), tp->t_when, &count);
	    cleanup_until(buf);
	    cleanup_push(str, xfree);
	    for (cp = str; *cp;)
		xputwchar(*cp++);
	    cleanup_until(str);
	}
	return;
    }

    if (*cp == '-') {
	/* remove item from list */
	if (!sched_ptr)
	    stderror(ERR_NOSCHED);
	if (*v)
	    stderror(ERR_SCHEDUSAGE);
	count = atoi(short2str(++cp));
	if (count <= 0)
	    stderror(ERR_SCHEDUSAGE);
	pp = &sched_ptr;
	tp = sched_ptr;
	while (--count) {
	    if (tp->t_next == 0)
		break;
	    else {
		pp = &tp->t_next;
		tp = tp->t_next;
	    }
	}
	if (count)
	    stderror(ERR_SCHEDEV);
	*pp = tp->t_next;
	blkfree(tp->t_lex);
	xfree(tp);
	return;
    }

    /* else, add an item to the list */
    if (!*v)
	stderror(ERR_SCHEDCOM);
    relative = 0;
    if (!Isdigit(*cp)) {	/* not abs. time */
	if (*cp != '+')
	    stderror(ERR_SCHEDUSAGE);
	cp++, relative++;
    }
    minutes = 0;
    hours = atoi(short2str(cp));
    while (*cp && *cp != ':' && *cp != 'a' && *cp != 'p')
	cp++;
    if (*cp && *cp == ':')
	minutes = atoi(short2str(++cp));
    if ((hours < 0) || (minutes < 0) ||
	(hours > 23) || (minutes > 59))
	stderror(ERR_SCHEDTIME);
    while (*cp && *cp != 'p' && *cp != 'a')
	cp++;
    if (*cp && relative)
	stderror(ERR_SCHEDREL);
    if (*cp == 'p')
	hours += 12;
    (void) time(&cur_time);
    ltp = localtime(&cur_time);
    if (relative) {
	dif_hour = hours;
	dif_min = minutes;
    }
    else {
	if ((dif_hour = hours - ltp->tm_hour) < 0)
	    dif_hour += 24;
	if ((dif_min = minutes - ltp->tm_min) < 0) {
	    dif_min += 60;
	    if ((--dif_hour) < 0)
		dif_hour = 23;
	}
    }
    tp = xcalloc(1, sizeof *tp);
#ifdef _SX
    tp->t_when = cur_time - ltp->tm_sec + dif_hour * 3600 + dif_min * 60;
#else	/* _SX */
    tp->t_when = cur_time - ltp->tm_sec + dif_hour * 3600L + dif_min * 60L;
#endif /* _SX */
    /* use of tm_sec: get to beginning of minute. */
    for (pp = &sched_ptr; *pp != NULL && tp->t_when >= (*pp)->t_when;
	 pp = &(*pp)->t_next)
	;
    tp->t_next = *pp;
    *pp = tp;
    tp->t_lex = saveblk(v);
}