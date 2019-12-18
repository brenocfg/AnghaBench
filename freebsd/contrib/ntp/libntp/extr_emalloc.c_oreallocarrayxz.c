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
 int /*<<< orphan*/  LOG_ERR ; 
 size_t MUL_NO_OVERFLOW ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 void* ereallocz (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 

void *
oreallocarrayxz(
	void *optr,
	size_t nmemb,
	size_t size,
	size_t extra
#ifdef EREALLOC_CALLSITE		/* ntp_malloc.h */
	,
	const char *	file,
	int		line
#endif
	)
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    nmemb > 0 && SIZE_MAX / nmemb < size) {
#ifndef EREALLOC_CALLSITE
		msyslog(LOG_ERR, "fatal allocation size overflow");
#else
		msyslog(LOG_ERR,
			"fatal allocation size overflow %s line %d",
			file, line);
#endif
		exit(1);
	}
#ifndef EREALLOC_CALLSITE
	return ereallocz(optr, extra + (size * nmemb), 0, TRUE);
#else
	return ereallocz(optr, extra + (size * nmemb), 0, TRUE, file, line);
#endif
}