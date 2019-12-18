#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  scalar_t__ wchar_t ;
struct xlocale_ctype {size_t (* __wcrtomb ) (char*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_4__ {int /*<<< orphan*/  _flags; int /*<<< orphan*/  _mbstate; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  WEOF ; 
 struct xlocale_ctype* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SERR ; 
 scalar_t__ __sputc (unsigned char,TYPE_1__*) ; 
 size_t stub1 (char*,scalar_t__,int /*<<< orphan*/ *) ; 

wint_t
__fputwc(wchar_t wc, FILE *fp, locale_t locale)
{
	char buf[MB_LEN_MAX];
	size_t i, len;
	struct xlocale_ctype *l = XLOCALE_CTYPE(locale);

	if ((len = l->__wcrtomb(buf, wc, &fp->_mbstate)) == (size_t)-1) {
		fp->_flags |= __SERR;
		return (WEOF);
	}

	for (i = 0; i < len; i++)
		if (__sputc((unsigned char)buf[i], fp) == EOF)
			return (WEOF);

	return ((wint_t)wc);
}