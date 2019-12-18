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
typedef  scalar_t__ nl_catd ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int catclose (scalar_t__) ; 
 scalar_t__ catd ; 
 scalar_t__ catgets_iconv ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  handle_pending_signals () ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 

void
nlsclose(void)
{
#ifdef NLS_CATALOGS
#if defined(HAVE_ICONV) && defined(HAVE_NL_LANGINFO)
    if (catgets_iconv != (iconv_t)-1) {
	iconv_close(catgets_iconv);
	catgets_iconv = (iconv_t)-1;
    }
#endif /* HAVE_ICONV && HAVE_NL_LANGINFO */
    if (catd != (nl_catd)-1) {
	/*
	 * catclose can call other functions which can call longjmp
	 * making us re-enter this code. Prevent infinite recursion
	 * by resetting catd. Problem reported and solved by:
	 * Gerhard Niklasch
	 */
	nl_catd oldcatd = catd;
	catd = (nl_catd)-1;
	while (catclose(oldcatd) == -1 && errno == EINTR)
	    handle_pending_signals();
    }
#endif /* NLS_CATALOGS */
}