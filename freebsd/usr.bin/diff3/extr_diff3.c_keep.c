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
struct range {scalar_t__ to; scalar_t__ from; } ;

/* Variables and functions */
 int /*<<< orphan*/  change (int,struct range*,int) ; 
 int* last ; 

__attribute__((used)) static void
keep(int i, struct range *rnew)
{
	int delta;
	struct range trange;

	delta = last[3] - last[i];
	trange.from = rnew->from - delta;
	trange.to = rnew->to - delta;
	change(i, &trange, true);
}