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
struct termp {scalar_t__ skipvsp; int /*<<< orphan*/  (* endline ) (struct termp*) ;scalar_t__ minbl; scalar_t__ viscol; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct termp*) ; 
 int /*<<< orphan*/  term_newln (struct termp*) ; 

void
term_vspace(struct termp *p)
{

	term_newln(p);
	p->viscol = 0;
	p->minbl = 0;
	if (0 < p->skipvsp)
		p->skipvsp--;
	else
		(*p->endline)(p);
}