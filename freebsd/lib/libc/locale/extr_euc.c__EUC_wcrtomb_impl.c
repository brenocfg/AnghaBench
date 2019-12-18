#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_2__ {scalar_t__ want; } ;
typedef  TYPE_1__ _EucState ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static size_t
_EUC_wcrtomb_impl(char * __restrict s, wchar_t wc,
    mbstate_t * __restrict ps,
    uint8_t cs2, uint8_t cs2width, uint8_t cs3, uint8_t cs3width)
{
	_EucState *es;
	int i, len;
	wchar_t nm;

	es = (_EucState *)ps;

	if (es->want != 0) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	if (s == NULL)
		/* Reset to initial shift state (no-op) */
		return (1);

	if ((wc & ~0x7f) == 0) {
		/* Fast path for plain ASCII (CS0) */
		*s = (char)wc;
		return (1);
	}

	/* Determine the "length" */
	if ((unsigned)wc > 0xffffff) {
		len = 4;
	} else if ((unsigned)wc > 0xffff) {
		len = 3;
	} else if ((unsigned)wc > 0xff) {
		len = 2;
	} else {
		len = 1;
	}

	if (len > MB_CUR_MAX) {
		errno = EILSEQ;
		return ((size_t)-1);
	}

	/* This first check excludes CS1, which is implicitly valid. */
	if ((wc < 0xa100) || (wc > 0xffff)) {
		/* Check for valid CS2 or CS3 */
		nm = (wc >> ((len - 1) * 8));
		if (nm == cs2) {
			if (len != cs2width) {
				errno = EILSEQ;
				return ((size_t)-1);
			}
		} else if (nm == cs3) {
			if (len != cs3width) {
				errno = EILSEQ;
				return ((size_t)-1);
			}
		} else {
			errno = EILSEQ;
			return ((size_t)-1);
		}
	}

	/* Stash the bytes, least significant last */
	for (i = len - 1; i >= 0; i--) {
		s[i] = (wc & 0xff);
		wc >>= 8;
	}
	return (len);
}