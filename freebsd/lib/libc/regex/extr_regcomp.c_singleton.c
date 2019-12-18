#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wint_t ;
struct TYPE_4__ {int nwides; scalar_t__ nranges; scalar_t__ ntypes; scalar_t__ icase; scalar_t__* wides; } ;
typedef  TYPE_1__ cset ;

/* Variables and functions */
 scalar_t__ CHIN (TYPE_1__*,scalar_t__) ; 
 scalar_t__ NC ; 
 scalar_t__ OUT ; 

__attribute__((used)) static wint_t
singleton(cset *cs)
{
	wint_t i, s, n;

	for (i = n = 0; i < NC; i++)
		if (CHIN(cs, i)) {
			n++;
			s = i;
		}
	if (n == 1)
		return (s);
	if (cs->nwides == 1 && cs->nranges == 0 && cs->ntypes == 0 &&
	    cs->icase == 0)
		return (cs->wides[0]);
	/* Don't bother handling the other cases. */
	return (OUT);
}