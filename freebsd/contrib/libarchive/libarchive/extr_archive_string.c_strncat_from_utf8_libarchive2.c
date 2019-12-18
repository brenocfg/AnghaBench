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
typedef  scalar_t__ uint32_t ;
struct archive_string_conv {int dummy; } ;
struct archive_string {size_t length; char* s; int buffer_length; } ;
typedef  int /*<<< orphan*/  shift_state ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 char* MB_CUR_MAX ; 
 int _utf8_to_unicode (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wcrtomb (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ wctomb (char*,int) ; 

__attribute__((used)) static int
strncat_from_utf8_libarchive2(struct archive_string *as,
    const void *_p, size_t len, struct archive_string_conv *sc)
{
	const char *s;
	int n;
	char *p;
	char *end;
	uint32_t unicode;
#if HAVE_WCRTOMB
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));
#else
	/* Clear the shift state before starting. */
	wctomb(NULL, L'\0');
#endif
	(void)sc; /* UNUSED */
	/*
	 * Allocate buffer for MBS.
	 * We need this allocation here since it is possible that
	 * as->s is still NULL.
	 */
	if (archive_string_ensure(as, as->length + len + 1) == NULL)
		return (-1);

	s = (const char *)_p;
	p = as->s + as->length;
	end = as->s + as->buffer_length - MB_CUR_MAX -1;
	while ((n = _utf8_to_unicode(&unicode, s, len)) != 0) {
		wchar_t wc;

		if (p >= end) {
			as->length = p - as->s;
			/* Re-allocate buffer for MBS. */
			if (archive_string_ensure(as,
			    as->length + len * 2 + 1) == NULL)
				return (-1);
			p = as->s + as->length;
			end = as->s + as->buffer_length - MB_CUR_MAX -1;
		}

		/*
		 * As libarchive 2.x, translates the UTF-8 characters into
		 * wide-characters in the assumption that WCS is Unicode.
		 */
		if (n < 0) {
			n *= -1;
			wc = L'?';
		} else
			wc = (wchar_t)unicode;

		s += n;
		len -= n;
		/*
		 * Translates the wide-character into the current locale MBS.
		 */
#if HAVE_WCRTOMB
		n = (int)wcrtomb(p, wc, &shift_state);
#else
		n = (int)wctomb(p, wc);
#endif
		if (n == -1)
			return (-1);
		p += n;
	}
	as->length = p - as->s;
	as->s[as->length] = '\0';
	return (0);
}