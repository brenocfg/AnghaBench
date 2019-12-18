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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  nfmt ;

/* Variables and functions */
 int GetLastError () ; 
 int NO_ERROR ; 
 int errno ; 
 int /*<<< orphan*/  format_errmsg (char const*,int,char const*,int) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int
mvsnprintf(
	char *		buf,
	size_t		bufsiz,
	const char *	fmt,
	va_list		ap
	)
{
#ifndef VSNPRINTF_PERCENT_M
	char		nfmt[256];
#else
	const char *	nfmt = fmt;
#endif
	int		errval;

	/*
	 * Save the error value as soon as possible
	 */
#ifdef SYS_WINNT
	errval = GetLastError();
	if (NO_ERROR == errval)
#endif /* SYS_WINNT */
		errval = errno;

#ifndef VSNPRINTF_PERCENT_M
	format_errmsg(nfmt, sizeof(nfmt), fmt, errval);
#else
	errno = errval;
#endif
	return vsnprintf(buf, bufsiz, nfmt, ap);
}