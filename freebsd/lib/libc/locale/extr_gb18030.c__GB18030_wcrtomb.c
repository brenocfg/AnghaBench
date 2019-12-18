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
struct TYPE_2__ {scalar_t__ count; } ;
typedef  TYPE_1__ _GB18030State ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static size_t
_GB18030_wcrtomb(char * __restrict s, wchar_t wc, mbstate_t * __restrict ps)
{
	_GB18030State *gs;
	size_t len;
	int c;

	gs = (_GB18030State *)ps;

	if (gs->count != 0) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	if (s == NULL)
		/* Reset to initial shift state (no-op) */
		return (1);
	if ((wc & ~0x7fffffff) != 0)
		goto ilseq;
	if (wc & 0x7f000000) {
		/* Replace high bit that mbrtowc() removed. */
		wc |= 0x80000000;
		c = (wc >> 24) & 0xff;
		if (c < 0x81 || c > 0xfe)
			goto ilseq;
		*s++ = c;
		c = (wc >> 16) & 0xff;
		if (c < 0x30 || c > 0x39)
			goto ilseq;
		*s++ = c;
		c = (wc >> 8) & 0xff;
		if (c < 0x81 || c > 0xfe)
			goto ilseq;
		*s++ = c;
		c = wc & 0xff;
		if (c < 0x30 || c > 0x39)
			goto ilseq;
		*s++ = c;
		len = 4;
	} else if (wc & 0x00ff0000)
		goto ilseq;
	else if (wc & 0x0000ff00) {
		c = (wc >> 8) & 0xff;
		if (c < 0x81 || c > 0xfe)
			goto ilseq;
		*s++ = c;
		c = wc & 0xff;
		if (c < 0x40 || c == 0x7f || c == 0xff)
			goto ilseq;
		*s++ = c;
		len = 2;
	} else if (wc <= 0x7f) {
		*s++ = wc;
		len = 1;
	} else
		goto ilseq;

	return (len);
ilseq:
	errno = EILSEQ;
	return ((size_t)-1);
}