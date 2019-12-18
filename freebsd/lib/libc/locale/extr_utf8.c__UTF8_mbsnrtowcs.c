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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_2__ {scalar_t__ want; } ;
typedef  TYPE_1__ _UTF8State ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 size_t _UTF8_mbrtowc (scalar_t__*,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static size_t
_UTF8_mbsnrtowcs(wchar_t * __restrict dst, const char ** __restrict src,
    size_t nms, size_t len, mbstate_t * __restrict ps)
{
	_UTF8State *us;
	const char *s;
	size_t nchr;
	wchar_t wc;
	size_t nb;

	us = (_UTF8State *)ps;

	s = *src;
	nchr = 0;

	if (dst == NULL) {
		/*
		 * The fast path in the loop below is not safe if an ASCII
		 * character appears as anything but the first byte of a
		 * multibyte sequence. Check now to avoid doing it in the loop.
		 */
		if (nms > 0 && us->want > 0 && (signed char)*s > 0) {
			errno = EILSEQ;
			return ((size_t)-1);
		}
		for (;;) {
			if (nms > 0 && (signed char)*s > 0)
				/*
				 * Fast path for plain ASCII characters
				 * excluding NUL.
				 */
				nb = 1;
			else if ((nb = _UTF8_mbrtowc(&wc, s, nms, ps)) ==
			    (size_t)-1)
				/* Invalid sequence - mbrtowc() sets errno. */
				return ((size_t)-1);
			else if (nb == 0 || nb == (size_t)-2)
				return (nchr);
			s += nb;
			nms -= nb;
			nchr++;
		}
		/*NOTREACHED*/
	}

	/*
	 * The fast path in the loop below is not safe if an ASCII
	 * character appears as anything but the first byte of a
	 * multibyte sequence. Check now to avoid doing it in the loop.
	 */
	if (nms > 0 && len > 0 && us->want > 0 && (signed char)*s > 0) {
		errno = EILSEQ;
		return ((size_t)-1);
	}
	while (len-- > 0) {
		if (nms > 0 && (signed char)*s > 0) {
			/*
			 * Fast path for plain ASCII characters
			 * excluding NUL.
			 */
			*dst = (wchar_t)*s;
			nb = 1;
		} else if ((nb = _UTF8_mbrtowc(dst, s, nms, ps)) ==
		    (size_t)-1) {
			*src = s;
			return ((size_t)-1);
		} else if (nb == (size_t)-2) {
			*src = s + nms;
			return (nchr);
		} else if (nb == 0) {
			*src = NULL;
			return (nchr);
		}
		s += nb;
		nms -= nb;
		nchr++;
		dst++;
	}
	*src = s;
	return (nchr);
}