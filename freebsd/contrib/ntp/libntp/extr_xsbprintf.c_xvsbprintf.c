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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int
xvsbprintf(
	char       **ppbuf,	/* pointer to buffer pointer (I/O) */
	char * const pend,	/* buffer end (I)		   */
	char const  *pfmt,	/* printf-like format string       */
	va_list      va		/* formatting args for above       */
	)
{
	char *pbuf = (ppbuf) ? *ppbuf : NULL;
	int   rc   = -1;
	if (pbuf && (pend - pbuf > 0)) {
		size_t blen = (size_t)(pend - pbuf);
		rc = vsnprintf(pbuf, blen, pfmt, va);
		if (rc > 0) {
		    if ((size_t)rc >= blen)
			rc = 0;
		    pbuf += rc;
		}
		*pbuf = '\0'; /* fear of bad vsnprintf */
		*ppbuf = pbuf;
	} else {
		errno = EINVAL;
	}
	return rc;
}