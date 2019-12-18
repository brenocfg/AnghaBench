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
struct logininfo {int dummy; } ;

/* Variables and functions */
 int lastlog_get_entry (struct logininfo*) ; 
 int utmpx_get_entry (struct logininfo*) ; 
 int wtmp_get_entry (struct logininfo*) ; 
 int wtmpx_get_entry (struct logininfo*) ; 

int
getlast_entry(struct logininfo *li)
{
#ifdef USE_LASTLOG
	return(lastlog_get_entry(li));
#else /* !USE_LASTLOG */
#if defined(USE_UTMPX) && defined(HAVE_SETUTXDB) && \
    defined(UTXDB_LASTLOGIN) && defined(HAVE_GETUTXUSER)
	return (utmpx_get_entry(li));
#endif

#if defined(DISABLE_LASTLOG)
	/* On some systems we shouldn't even try to obtain last login
	 * time, e.g. AIX */
	return (0);
# elif defined(USE_WTMP) && \
    (defined(HAVE_TIME_IN_UTMP) || defined(HAVE_TV_IN_UTMP))
	/* retrieve last login time from utmp */
	return (wtmp_get_entry(li));
# elif defined(USE_WTMPX) && \
    (defined(HAVE_TIME_IN_UTMPX) || defined(HAVE_TV_IN_UTMPX))
	/* If wtmp isn't available, try wtmpx */
	return (wtmpx_get_entry(li));
# else
	/* Give up: No means of retrieving last login time */
	return (0);
# endif /* DISABLE_LASTLOG */
#endif /* USE_LASTLOG */
}