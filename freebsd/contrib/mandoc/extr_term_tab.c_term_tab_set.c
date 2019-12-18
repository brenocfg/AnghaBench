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
struct termp {int dummy; } ;
struct tablist {size_t n; size_t s; size_t* t; } ;
struct roffsu {int dummy; } ;
struct TYPE_2__ {scalar_t__ d; struct tablist a; struct tablist p; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE_EM ; 
 int /*<<< orphan*/  SCALE_IN ; 
 int /*<<< orphan*/ * a2roffsu (char const*,struct roffsu*,int /*<<< orphan*/ ) ; 
 size_t* mandoc_reallocarray (size_t*,size_t,int) ; 
 TYPE_1__ tabs ; 
 void* term_hen (struct termp const*,struct roffsu*) ; 

void
term_tab_set(const struct termp *p, const char *arg)
{
	static int	 recording_period;

	struct roffsu	 su;
	struct tablist	*tl;
	size_t		 pos;
	int		 add;

	/* Special arguments: clear all tabs or switch lists. */

	if (arg == NULL) {
		tabs.a.n = tabs.p.n = 0;
		recording_period = 0;
		if (tabs.d == 0) {
			a2roffsu(".8i", &su, SCALE_IN);
			tabs.d = term_hen(p, &su);
		}
		return;
	}
	if (arg[0] == 'T' && arg[1] == '\0') {
		recording_period = 1;
		return;
	}

	/* Parse the sign, the number, and the unit. */

	if (*arg == '+') {
		add = 1;
		arg++;
	} else
		add = 0;
	if (a2roffsu(arg, &su, SCALE_EM) == NULL)
		return;

	/* Select the list, and extend it if it is full. */

	tl = recording_period ? &tabs.p : &tabs.a;
	if (tl->n >= tl->s) {
		tl->s += 8;
		tl->t = mandoc_reallocarray(tl->t, tl->s, sizeof(*tl->t));
	}

	/* Append the new position. */

	pos = term_hen(p, &su);
	tl->t[tl->n] = pos;
	if (add && tl->n)
		tl->t[tl->n] += tl->t[tl->n - 1];
	tl->n++;
}