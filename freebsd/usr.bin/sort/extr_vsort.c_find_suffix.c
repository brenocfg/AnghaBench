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
typedef  scalar_t__ bwstring_iterator ;

/* Variables and functions */
 int bws_get_iter_value (scalar_t__) ; 
 scalar_t__ bws_iterator_inc (scalar_t__,int) ; 
 int /*<<< orphan*/  isalnum_clocale (int) ; 
 int /*<<< orphan*/  isalpha_clocale (int) ; 

__attribute__((used)) static void
find_suffix(bwstring_iterator si, bwstring_iterator se, size_t *len)
{
	wchar_t c;
	size_t clen;
	bool expect_alpha, sfx;

	sfx = false;
	expect_alpha = false;
	*len = 0;
	clen = 0;

	while ((si < se) && (c = bws_get_iter_value(si))) {
		if (expect_alpha) {
			expect_alpha = false;
			if (!isalpha_clocale(c) && (c != L'~'))
				sfx = false;
		} else if (c == L'.') {
			expect_alpha = true;
			if (!sfx) {
				sfx = true;
				*len = clen;
			}
		} else if (!isalnum_clocale(c) && (c != L'~'))
			sfx = false;

		si = bws_iterator_inc(si, 1);
		++clen;
	}

	/* This code must be here to make the implementation compatible
	 * with WORDING of GNU sort documentation.
	 * But the GNU sort implementation is not following its own
	 * documentation.  GNU sort allows empty file extensions
	 * (just dot with nothing after); but the regular expression in
	 * their documentation does not allow empty file extensions.
	 * We chose to make our implementation compatible with GNU sort
	 * implementation.  If they will ever fix their bug, this code
	 * must be uncommented. Or they may choose to fix the info page,
	 * then the code stays commented.
	 *
	 if (expect_alpha)
	 	sfx = false;
	 */

	if (!sfx)
		*len = clen;
}