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
typedef  int /*<<< orphan*/  wmsk ;
typedef  int wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ ISGRAPH (int,int) ; 
 int NBBY ; 
 int VIS_SAFE ; 
 int /*<<< orphan*/ * do_mbyte (int /*<<< orphan*/ *,int,int,int,int) ; 
 scalar_t__ iswsafe (int) ; 
 scalar_t__ iswwhite (int) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static wchar_t *
do_svis(wchar_t *dst, wint_t c, int flags, wint_t nextc, const wchar_t *extra)
{
	int iswextra, i, shft;
	uint64_t bmsk, wmsk;

	iswextra = wcschr(extra, c) != NULL;
	if (!iswextra && (ISGRAPH(flags, c) || iswwhite(c) ||
	    ((flags & VIS_SAFE) && iswsafe(c)))) {
		*dst++ = c;
		return dst;
	}

	/* See comment in istrsenvisx() output loop, below. */
	wmsk = 0;
	for (i = sizeof(wmsk) - 1; i >= 0; i--) {
		shft = i * NBBY;
		bmsk = (uint64_t)0xffLL << shft;
		wmsk |= bmsk;
		if ((c & wmsk) || i == 0)
			dst = do_mbyte(dst, (wint_t)(
			    (uint64_t)(c & bmsk) >> shft),
			    flags, nextc, iswextra);
	}

	return dst;
}