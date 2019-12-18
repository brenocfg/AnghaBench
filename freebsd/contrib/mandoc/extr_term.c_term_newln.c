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
struct termp {scalar_t__ viscol; TYPE_1__* tcol; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ lastcol; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERMP_NOSPACE ; 
 int /*<<< orphan*/  term_flushln (struct termp*) ; 

void
term_newln(struct termp *p)
{

	p->flags |= TERMP_NOSPACE;
	if (p->tcol->lastcol || p->viscol)
		term_flushln(p);
}