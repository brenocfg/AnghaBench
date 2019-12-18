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
struct TYPE_4__ {int y; int m; int d; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int /*<<< orphan*/  sdater (int,TYPE_1__*) ; 
 int sndaysr (TYPE_1__*) ; 

__attribute__((used)) static int
firstday(int y, int m)
{
	date dt;
	int nd;

	dt.y = y;
	dt.m = m;
	dt.d = 1;
	nd = sndaysr(&dt);
	for (;;) {
		sdater(nd, &dt);
		if ((dt.m >= m && dt.y == y) || dt.y > y)
			return (nd);
		else
			nd++;
	}
	/* NEVER REACHED */
}