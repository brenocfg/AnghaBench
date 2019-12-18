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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* SUPPRESS_PTR ; 
 int /*<<< orphan*/  WEOF ; 
 int /*<<< orphan*/  __fgetwc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_mbs ; 
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
convert_char(FILE *fp, char * mbp, int width, locale_t locale)
{
	mbstate_t mbs;
	size_t nconv;
	wint_t wi;
	int n;

	n = 0;
	mbs = initial_mbs;
	while (width-- != 0 && (wi = __fgetwc(fp, locale)) != WEOF) {
		if (mbp != SUPPRESS_PTR) {
			nconv = wcrtomb(mbp, wi, &mbs);
			if (nconv == (size_t)-1)
				return (-1);
			mbp += nconv;
		}
		n++;
	}
	if (n == 0)
		return (-1);
	return (n);
}