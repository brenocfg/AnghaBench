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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbsinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char const*) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 

extern size_t
tuklib_mbstr_width(const char *str, size_t *bytes)
{
	const size_t len = strlen(str);
	if (bytes != NULL)
		*bytes = len;

#if !(defined(HAVE_MBRTOWC) && defined(HAVE_WCWIDTH))
	// In single-byte mode, the width of the string is the same
	// as its length.
	return len;

#else
	mbstate_t state;
	memset(&state, 0, sizeof(state));

	size_t width = 0;
	size_t i = 0;

	// Convert one multibyte character at a time to wchar_t
	// and get its width using wcwidth().
	while (i < len) {
		wchar_t wc;
		const size_t ret = mbrtowc(&wc, str + i, len - i, &state);
		if (ret < 1 || ret > len)
			return (size_t)-1;

		i += ret;

		const int wc_width = wcwidth(wc);
		if (wc_width < 0)
			return (size_t)-1;

		width += wc_width;
	}

	// Require that the string ends in the initial shift state.
	// This way the caller can be combine the string with other
	// strings without needing to worry about the shift states.
	if (!mbsinit(&state))
		return (size_t)-1;

	return width;
#endif
}