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
struct archive_string_conv {int dummy; } ;
typedef  int /*<<< orphan*/  shift_state ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t mbtowc (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
invalid_mbs(const void *_p, size_t n, struct archive_string_conv *sc)
{
	const char *p = (const char *)_p;
	size_t r;

#if HAVE_MBRTOWC
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));
#else
	/* Clear the shift state before starting. */
	mbtowc(NULL, NULL, 0);
#endif
	while (n) {
		wchar_t wc;

#if HAVE_MBRTOWC
		r = mbrtowc(&wc, p, n, &shift_state);
#else
		r = mbtowc(&wc, p, n);
#endif
		if (r == (size_t)-1 || r == (size_t)-2)
			return (-1);/* Invalid. */
		if (r == 0)
			break;
		p += r;
		n -= r;
	}
	(void)sc; /* UNUSED */
	return (0); /* All Okey. */
}