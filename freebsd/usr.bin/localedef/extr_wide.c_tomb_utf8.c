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
typedef  int wchar_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  werr (char*,int) ; 

int
tomb_utf8(char *mb, wchar_t wc)
{
	uint8_t *s = (uint8_t *)mb;
	uint8_t msk;
	int cnt;
	int i;

	if (wc <= 0x7f) {
		s[0] = wc & 0x7f;
		s[1] = 0;
		return (1);
	}
	if (wc <= 0x7ff) {
		cnt = 2;
		msk = 0xc0;
	} else if (wc <= 0xffff) {
		cnt = 3;
		msk = 0xe0;
	} else if (wc <= 0x1fffff) {
		cnt = 4;
		msk = 0xf0;
	} else {
		werr("illegal uf8 char (%x)", wc);
		return (-1);
	}
	for (i = cnt - 1; i; i--) {
		s[i] = (wc & 0x3f) | 0x80;
		wc >>= 6;
	}
	s[0] = (msk) | wc;
	s[cnt] = 0;
	return (cnt);
}