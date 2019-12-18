#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int wint_t ;
typedef  int wchar_t ;
struct xlocale_ctype {size_t (* __mbrtowc ) (int*,size_t,size_t,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_5__ {size_t _r; size_t _p; int /*<<< orphan*/  _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int WEOF ; 
 struct xlocale_ctype* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SERR ; 
 scalar_t__ __sfeof (TYPE_1__*) ; 
 scalar_t__ __srefill (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 size_t stub1 (int*,size_t,size_t,int /*<<< orphan*/ *) ; 

wint_t 
__fgetwc_mbs(FILE *fp, mbstate_t *mbs, int *nread, locale_t locale)
{
	wchar_t wc;
	size_t nconv;
	struct xlocale_ctype *l = XLOCALE_CTYPE(locale);

	*nread = 0;
	if (fp->_r <= 0 && __srefill(fp))
		return (WEOF);
	do {
		nconv = l->__mbrtowc(&wc, fp->_p, fp->_r, mbs);
		if (nconv == (size_t)-1) {
			fp->_flags |= __SERR;
			return (WEOF);
		} else if (nconv == (size_t)-2)
			continue;
		else if (nconv == 0) {
			fp->_p++;
			fp->_r--;
			(*nread)++;
			return (L'\0');
		} else {
			fp->_p += nconv;
			fp->_r -= nconv;
			*nread += nconv;
			return (wc);
		}
	} while (__srefill(fp) == 0);
	if (__sfeof(fp)) {
		fp->_flags |= __SERR;
		errno = EILSEQ;
	}
	return (WEOF);
}