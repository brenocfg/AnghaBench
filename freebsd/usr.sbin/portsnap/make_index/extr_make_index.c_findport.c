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
struct TYPE_4__ {int /*<<< orphan*/  portdir; } ;
typedef  TYPE_1__ PORT ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int portcompare (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static PORT *
findport(PORT ** pp, size_t st, size_t en, char * name, char * from)
{
	size_t mid;
	int r;

	if (st == en)
		errx(1, "%s: no entry for %s", from, name);

	mid = (st + en) / 2;
	r = portcompare(pp[mid]->portdir, name);

	if (r == 0) {
		free(name);
		return pp[mid];
	} else if (r < 0)
		return findport(pp, mid + 1, en, name, from);
	else
		return findport(pp, st, mid, name, from);
}