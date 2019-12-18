#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkgname; } ;
typedef  TYPE_1__ PORT ;
typedef  TYPE_2__ DEP ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
heapifypkgs(DEP * d, size_t size, size_t pos)
{
	size_t i = pos;
	PORT * tmp;

top:
	/* Find the largest value out of {pos, 2*pos+1, 2*pos+2} */
	if ((2 * pos + 1 < size) &&
	    (strcmp(d[i].p->pkgname, d[2 * pos + 1].p->pkgname) < 0))
		i = 2 * pos + 1;
	if ((2 * pos + 2 < size) &&
	    (strcmp(d[i].p->pkgname, d[2 * pos + 2].p->pkgname) < 0))
		i = 2 * pos + 2;

	/* If necessary, swap elements and iterate down the tree. */
	if (i != pos) {
		tmp = d[pos].p;
		d[pos].p = d[i].p;
		d[i].p = tmp;
		pos = i;
		goto top;
	}
}