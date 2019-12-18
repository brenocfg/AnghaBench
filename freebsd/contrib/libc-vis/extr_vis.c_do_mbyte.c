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
typedef  int wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int u_int32_t ;
typedef  void* u_char ;

/* Variables and functions */
#define  BELL 128 
 int /*<<< orphan*/  ISGRAPH (int,int) ; 
 int VIS_CSTYLE ; 
 int VIS_NOSLASH ; 
 int VIS_OCTAL ; 
 scalar_t__ iswcntrl (int) ; 
 int /*<<< orphan*/  iswoctal (int) ; 

__attribute__((used)) static wchar_t *
do_mbyte(wchar_t *dst, wint_t c, int flags, wint_t nextc, int iswextra)
{
	if (flags & VIS_CSTYLE) {
		switch (c) {
		case L'\n':
			*dst++ = L'\\'; *dst++ = L'n';
			return dst;
		case L'\r':
			*dst++ = L'\\'; *dst++ = L'r';
			return dst;
		case L'\b':
			*dst++ = L'\\'; *dst++ = L'b';
			return dst;
		case BELL:
			*dst++ = L'\\'; *dst++ = L'a';
			return dst;
		case L'\v':
			*dst++ = L'\\'; *dst++ = L'v';
			return dst;
		case L'\t':
			*dst++ = L'\\'; *dst++ = L't';
			return dst;
		case L'\f':
			*dst++ = L'\\'; *dst++ = L'f';
			return dst;
		case L' ':
			*dst++ = L'\\'; *dst++ = L's';
			return dst;
		case L'\0':
			*dst++ = L'\\'; *dst++ = L'0';
			if (iswoctal(nextc)) {
				*dst++ = L'0';
				*dst++ = L'0';
			}
			return dst;
		/* We cannot encode these characters in VIS_CSTYLE
		 * because they special meaning */
		case L'n':
		case L'r':
		case L'b':
		case L'a':
		case L'v':
		case L't':
		case L'f':
		case L's':
		case L'0':
		case L'M':
		case L'^':
		case L'$': /* vis(1) -l */
			break;
		default:
			if (ISGRAPH(flags, c) && !iswoctal(c)) {
				*dst++ = L'\\';
				*dst++ = c;
				return dst;
			}
		}
	}
	if (iswextra || ((c & 0177) == L' ') || (flags & VIS_OCTAL)) {
		*dst++ = L'\\';
		*dst++ = (u_char)(((u_int32_t)(u_char)c >> 6) & 03) + L'0';
		*dst++ = (u_char)(((u_int32_t)(u_char)c >> 3) & 07) + L'0';
		*dst++ =			     (c	      & 07) + L'0';
	} else {
		if ((flags & VIS_NOSLASH) == 0)
			*dst++ = L'\\';

		if (c & 0200) {
			c &= 0177;
			*dst++ = L'M';
		}

		if (iswcntrl(c)) {
			*dst++ = L'^';
			if (c == 0177)
				*dst++ = L'?';
			else
				*dst++ = c + L'@';
		} else {
			*dst++ = L'-';
			*dst++ = c;
		}
	}

	return dst;
}