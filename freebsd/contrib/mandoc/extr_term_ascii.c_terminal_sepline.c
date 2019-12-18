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
struct termp {size_t defrmargin; int /*<<< orphan*/  (* endline ) (struct termp*) ;int /*<<< orphan*/  (* letter ) (struct termp*,char) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct termp*) ; 
 int /*<<< orphan*/  stub2 (struct termp*,char) ; 
 int /*<<< orphan*/  stub3 (struct termp*) ; 
 int /*<<< orphan*/  stub4 (struct termp*) ; 

void
terminal_sepline(void *arg)
{
	struct termp	*p;
	size_t		 i;

	p = (struct termp *)arg;
	(*p->endline)(p);
	for (i = 0; i < p->defrmargin; i++)
		(*p->letter)(p, '-');
	(*p->endline)(p);
	(*p->endline)(p);
}