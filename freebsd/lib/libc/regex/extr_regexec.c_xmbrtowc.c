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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline size_t
xmbrtowc(wint_t *wi, const char *s, size_t n, mbstate_t *mbs, wint_t dummy)
{
	size_t nr;
	wchar_t wc;

	nr = mbrtowc(&wc, s, n, mbs);
	if (wi != NULL)
		*wi = wc;
	if (nr == 0)
		return (1);
	else if (nr == (size_t)-1 || nr == (size_t)-2) {
		memset(mbs, 0, sizeof(*mbs));
		if (wi != NULL)
			*wi = dummy;
		return (1);
	} else
                return (nr);
}