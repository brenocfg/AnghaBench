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
struct termp {int fonti; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
term_fontpopq(struct termp *p, int i)
{

	assert(i >= 0);
	if (p->fonti > i)
		p->fonti = i;
}