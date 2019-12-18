#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int wint_t ;
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_9__ {size_t _size; scalar_t__ _base; } ;
struct TYPE_10__ {int _flags; TYPE_1__ _lb; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_2__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 size_t GROW ; 
 int /*<<< orphan*/  ORIENT (TYPE_2__*,int) ; 
 int WEOF ; 
 int __SERR ; 
 int __fgetwc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __sferror (TYPE_2__*) ; 
 scalar_t__ __slbexpand (TYPE_2__*,size_t) ; 

wchar_t *
fgetwln_l(FILE * __restrict fp, size_t *lenp, locale_t locale)
{
	wchar_t *ret;
	wint_t wc;
	size_t len;
	int savserr;

	FIX_LOCALE(locale);

	FLOCKFILE_CANCELSAFE(fp);
	ORIENT(fp, 1);

	savserr = fp->_flags & __SERR;
	fp->_flags &= ~__SERR;

	len = 0;
	while ((wc = __fgetwc(fp, locale)) != WEOF) {
#define	GROW	512
		if (len * sizeof(wchar_t) >= fp->_lb._size &&
		    __slbexpand(fp, (len + GROW) * sizeof(wchar_t))) {
			fp->_flags |= __SERR;
			goto error;
		}
		*((wchar_t *)fp->_lb._base + len++) = wc;
		if (wc == L'\n')
			break;
	}
	/* fgetwc(3) may set both __SEOF and __SERR at once. */
	if (__sferror(fp))
		goto error;

	fp->_flags |= savserr;
	if (len == 0)
		goto error;

	*lenp = len;
	ret = (wchar_t *)fp->_lb._base;
end:
	FUNLOCKFILE_CANCELSAFE();
	return (ret);

error:
	*lenp = 0;
	ret = NULL;
	goto end;
}