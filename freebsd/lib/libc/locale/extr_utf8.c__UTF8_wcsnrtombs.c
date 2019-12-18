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
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_2__ {scalar_t__ want; } ;
typedef  TYPE_1__ _UTF8State ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MB_CUR_MAX ; 
 int MB_LEN_MAX ; 
 size_t _UTF8_wcrtomb (char*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static size_t
_UTF8_wcsnrtombs(char * __restrict dst, const wchar_t ** __restrict src,
    size_t nwc, size_t len, mbstate_t * __restrict ps)
{
	_UTF8State *us;
	char buf[MB_LEN_MAX];
	const wchar_t *s;
	size_t nbytes;
	size_t nb;

	us = (_UTF8State *)ps;

	if (us->want != 0) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	s = *src;
	nbytes = 0;

	if (dst == NULL) {
		while (nwc-- > 0) {
			if (0 <= *s && *s < 0x80)
				/* Fast path for plain ASCII characters. */
				nb = 1;
			else if ((nb = _UTF8_wcrtomb(buf, *s, ps)) ==
			    (size_t)-1)
				/* Invalid character - wcrtomb() sets errno. */
				return ((size_t)-1);
			if (*s == L'\0')
				return (nbytes + nb - 1);
			s++;
			nbytes += nb;
		}
		return (nbytes);
	}

	while (len > 0 && nwc-- > 0) {
		if (0 <= *s && *s < 0x80) {
			/* Fast path for plain ASCII characters. */
			nb = 1;
			*dst = *s;
		} else if (len > (size_t)MB_CUR_MAX) {
			/* Enough space to translate in-place. */
			if ((nb = _UTF8_wcrtomb(dst, *s, ps)) == (size_t)-1) {
				*src = s;
				return ((size_t)-1);
			}
		} else {
			/*
			 * May not be enough space; use temp. buffer.
			 */
			if ((nb = _UTF8_wcrtomb(buf, *s, ps)) == (size_t)-1) {
				*src = s;
				return ((size_t)-1);
			}
			if (nb > (int)len)
				/* MB sequence for character won't fit. */
				break;
			memcpy(dst, buf, nb);
		}
		if (*s == L'\0') {
			*src = NULL;
			return (nbytes + nb - 1);
		}
		s++;
		dst += nb;
		len -= nb;
		nbytes += nb;
	}
	*src = s;
	return (nbytes);
}