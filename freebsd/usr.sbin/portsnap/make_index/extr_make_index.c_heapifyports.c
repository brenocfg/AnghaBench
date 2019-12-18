#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  portdir; } ;
typedef  TYPE_1__ PORT ;

/* Variables and functions */
 scalar_t__ portcompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
heapifyports(PORT **pp, size_t size, size_t pos)
{
	size_t i = pos;
	PORT * tmp;

top:
	/* Find the largest value out of {pos, 2*pos+1, 2*pos+2} */
	if ((2 * pos + 1 < size) &&
	    (portcompare(pp[i]->portdir, pp[2 * pos + 1]->portdir) < 0))
		i = 2 * pos + 1;
	if ((2 * pos + 2 < size) &&
	    (portcompare(pp[i]->portdir, pp[2 * pos + 2]->portdir) < 0))
		i = 2 * pos + 2;

	/* If necessary, swap elements and iterate down the tree. */
	if (i != pos) {
		tmp = pp[pos];
		pp[pos] = pp[i];
		pp[i] = tmp;
		pos = i;
		goto top;
	}
}