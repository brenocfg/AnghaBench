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
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__* SUPPRESS_PTR ; 
 scalar_t__ WEOF ; 
 scalar_t__ __fgetwc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
convert_wchar(FILE *fp, wchar_t *wcp, int width, locale_t locale)
{
	wint_t wi;
	int n;

	n = 0;
	while (width-- != 0 && (wi = __fgetwc(fp, locale)) != WEOF) {
		if (wcp != SUPPRESS_PTR)
			*wcp++ = (wchar_t)wi;
		n++;
	}
	if (n == 0)
		return (-1);
	return (n);
}