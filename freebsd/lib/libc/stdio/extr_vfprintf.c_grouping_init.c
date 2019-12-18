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
struct lconv {int* grouping; int /*<<< orphan*/  thousands_sep; } ;
struct grouping_state {int* grouping; int thousep_len; int nseps; int nrepeats; int lead; int /*<<< orphan*/  thousands_sep; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int CHAR_MAX ; 
 struct lconv* localeconv_l (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grouping_init(struct grouping_state *gs, int ndigits, locale_t loc)
{
	struct lconv *locale;

	locale = localeconv_l(loc);
	gs->grouping = locale->grouping;
	gs->thousands_sep = locale->thousands_sep;
	gs->thousep_len = strlen(gs->thousands_sep);

	gs->nseps = gs->nrepeats = 0;
	gs->lead = ndigits;
	while (*gs->grouping != CHAR_MAX) {
		if (gs->lead <= *gs->grouping)
			break;
		gs->lead -= *gs->grouping;
		if (*(gs->grouping+1)) {
			gs->nseps++;
			gs->grouping++;
		} else
			gs->nrepeats++;
	}
	return ((gs->nseps + gs->nrepeats) * gs->thousep_len);
}