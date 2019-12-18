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

/* Variables and functions */
 void* XTOA (unsigned int) ; 
 int /*<<< orphan*/ * do_svis (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ iswspace (int) ; 
 int /*<<< orphan*/ * wcschr (char*,int) ; 

__attribute__((used)) static wchar_t *
do_mvis(wchar_t *dst, wint_t c, int flags, wint_t nextc, const wchar_t *extra)
{
	if ((c != L'\n') &&
	    /* Space at the end of the line */
	    ((iswspace(c) && (nextc == L'\r' || nextc == L'\n')) ||
	    /* Out of range */
	    (!iswspace(c) && (c < 33 || (c > 60 && c < 62) || c > 126)) ||
	    /* Specific char to be escaped */
	    wcschr(L"#$@[\\]^`{|}~", c) != NULL)) {
		*dst++ = L'=';
		*dst++ = XTOA(((unsigned int)c >> 4) & 0xf);
		*dst++ = XTOA((unsigned int)c & 0xf);
	} else
		dst = do_svis(dst, c, flags, nextc, extra);
	return dst;
}