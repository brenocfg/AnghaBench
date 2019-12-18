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
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  EVUTIL_ISALNUM_ (char const) ; 
 int /*<<< orphan*/  EVUTIL_ISALPHA_ (char const) ; 

__attribute__((used)) static int
scheme_ok(const char *s, const char *eos)
{
	/* scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) */
	EVUTIL_ASSERT(eos >= s);
	if (s == eos)
		return 0;
	if (!EVUTIL_ISALPHA_(*s))
		return 0;
	while (++s < eos) {
		if (! EVUTIL_ISALNUM_(*s) &&
		    *s != '+' && *s != '-' && *s != '.')
			return 0;
	}
	return 1;
}