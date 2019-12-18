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

/* Variables and functions */
 int /*<<< orphan*/  CODESET ; 
 char const* locale_charset () ; 
 char const* nl_langinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
default_iconv_charset(const char *charset) {
	if (charset != NULL && charset[0] != '\0')
		return charset;
#if HAVE_LOCALE_CHARSET && !defined(__APPLE__)
	/* locale_charset() is broken on Mac OS */
	return locale_charset();
#elif HAVE_NL_LANGINFO
	return nl_langinfo(CODESET);
#else
	return "";
#endif
}