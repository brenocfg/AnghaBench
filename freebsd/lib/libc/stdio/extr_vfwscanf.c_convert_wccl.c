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
struct ccl {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__* SUPPRESS_PTR ; 
 scalar_t__ WEOF ; 
 scalar_t__ __fgetwc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ungetwc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ inccl (struct ccl const*,scalar_t__) ; 

__attribute__((used)) static __inline int
convert_wccl(FILE *fp, wchar_t *wcp, int width, const struct ccl *ccl,
    locale_t locale)
{
	wchar_t *wcp0;
	wint_t wi;
	int n;

	if (wcp == SUPPRESS_PTR) {
		n = 0;
		while ((wi = __fgetwc(fp, locale)) != WEOF &&
		    width-- != 0 && inccl(ccl, wi))
			n++;
		if (wi != WEOF)
			__ungetwc(wi, fp, locale);
	} else {
		wcp0 = wcp;
		while ((wi = __fgetwc(fp, locale)) != WEOF &&
		    width-- != 0 && inccl(ccl, wi))
			*wcp++ = (wchar_t)wi;
		if (wi != WEOF)
			__ungetwc(wi, fp, locale);
		n = wcp - wcp0;
		if (n == 0)
			return (0);
		*wcp = 0;
	}
	return (n);
}