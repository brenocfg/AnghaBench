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
struct archive_wstring {size_t length; int* s; } ;
typedef  int /*<<< orphan*/  shift_state ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 scalar_t__ EILSEQ ; 
 int /*<<< orphan*/ * archive_wstring_ensure (struct archive_wstring*,size_t) ; 
 scalar_t__ errno ; 
 size_t mbrtowc (int*,char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t mbtowc (int*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
archive_wstring_append_from_mbs(struct archive_wstring *dest,
    const char *p, size_t len)
{
	size_t r;
	int ret_val = 0;
	/*
	 * No single byte will be more than one wide character,
	 * so this length estimate will always be big enough.
	 */
	size_t wcs_length = len;
	size_t mbs_length = len;
	const char *mbs = p;
	wchar_t *wcs;
#if HAVE_MBRTOWC
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));
#endif
	if (NULL == archive_wstring_ensure(dest, dest->length + wcs_length + 1))
		return (-1);
	wcs = dest->s + dest->length;
	/*
	 * We cannot use mbsrtowcs/mbstowcs here because those may convert
	 * extra MBS when strlen(p) > len and one wide character consists of
	 * multi bytes.
	 */
	while (*mbs && mbs_length > 0) {
		if (wcs_length == 0) {
			dest->length = wcs - dest->s;
			dest->s[dest->length] = L'\0';
			wcs_length = mbs_length;
			if (NULL == archive_wstring_ensure(dest,
			    dest->length + wcs_length + 1))
				return (-1);
			wcs = dest->s + dest->length;
		}
#if HAVE_MBRTOWC
		r = mbrtowc(wcs, mbs, wcs_length, &shift_state);
#else
		r = mbtowc(wcs, mbs, wcs_length);
#endif
		if (r == (size_t)-1 || r == (size_t)-2) {
			ret_val = -1;
			if (errno == EILSEQ) {
				++mbs;
				--mbs_length;
				continue;
			} else
				break;
		}
		if (r == 0 || r > mbs_length)
			break;
		wcs++;
		wcs_length--;
		mbs += r;
		mbs_length -= r;
	}
	dest->length = wcs - dest->s;
	dest->s[dest->length] = L'\0';
	return (ret_val);
}