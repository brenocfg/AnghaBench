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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* SUPPRESS_PTR ; 
 scalar_t__ WEOF ; 
 scalar_t__ __fgetwc_mbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/  __ungetwc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_mbs ; 
 int /*<<< orphan*/  iswspace (scalar_t__) ; 

__attribute__((used)) static __inline int
convert_wstring(FILE *fp, wchar_t *wcp, int width, locale_t locale)
{
	mbstate_t mbs;
	wint_t wi;
	int n, nread;

	mbs = initial_mbs;
	n = 0;
	if (wcp == SUPPRESS_PTR) {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && !iswspace(wi))
			n += nread;
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
	} else {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && !iswspace(wi)) {
			*wcp++ = (wchar_t)wi;
			n += nread;
		}
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
		*wcp = '\0';
	}
	return (n);
}