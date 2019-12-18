#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grouping_state {int* grouping; int nseps; int nrepeats; int lead; int /*<<< orphan*/  thousands_sep; } ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_2__ {int* grouping; } ;

/* Variables and functions */
 int CHAR_MAX ; 
 int /*<<< orphan*/  get_thousep (int /*<<< orphan*/ ) ; 
 TYPE_1__* localeconv_l (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grouping_init(struct grouping_state *gs, int ndigits, locale_t locale)
{

	gs->grouping = localeconv_l(locale)->grouping;
	gs->thousands_sep = get_thousep(locale);

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
	return (gs->nseps + gs->nrepeats);
}