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
typedef  scalar_t__ wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__* SUPPRESS_PTR ; 
 scalar_t__ WEOF ; 
 scalar_t__ __fgetwc_mbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/  __ungetwc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_mbs ; 
 size_t wctob (scalar_t__) ; 

__attribute__((used)) static __inline int
convert_wccl(FILE *fp, wchar_t *wcp, int width, const char *ccltab,
    locale_t locale)
{
	mbstate_t mbs;
	wint_t wi;
	int n, nread;

	mbs = initial_mbs;
	n = 0;
	if (wcp == SUPPRESS_PTR) {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && ccltab[wctob(wi)])
			n += nread;
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
	} else {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && ccltab[wctob(wi)]) {
			*wcp++ = (wchar_t)wi;
			n += nread;
		}
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
		if (n == 0)
			return (0);
		*wcp = 0;
	}
	return (n);
}