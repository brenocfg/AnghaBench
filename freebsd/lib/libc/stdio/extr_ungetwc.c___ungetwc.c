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
struct xlocale_ctype {size_t (* __wcrtomb ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_4__ {int /*<<< orphan*/  _flags; int /*<<< orphan*/  _mbstate; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  WEOF ; 
 struct xlocale_ctype* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SERR ; 
 scalar_t__ __ungetc (unsigned char,TYPE_1__*) ; 
 size_t stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

wint_t
__ungetwc(wint_t wc, FILE *fp, locale_t locale)
{
	char buf[MB_LEN_MAX];
	size_t len;
	struct xlocale_ctype *l = XLOCALE_CTYPE(locale);

	if (wc == WEOF)
		return (WEOF);
	if ((len = l->__wcrtomb(buf, wc, &fp->_mbstate)) == (size_t)-1) {
		fp->_flags |= __SERR;
		return (WEOF);
	}
	while (len-- != 0)
		if (__ungetc((unsigned char)buf[len], fp) == EOF)
			return (WEOF);

	return (wc);
}