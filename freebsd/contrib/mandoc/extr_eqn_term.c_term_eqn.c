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
struct termp {int /*<<< orphan*/  flags; } ;
struct eqn_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERMP_NOSPACE ; 
 int /*<<< orphan*/  eqn_box (struct termp*,struct eqn_box const*) ; 

void
term_eqn(struct termp *p, const struct eqn_box *bp)
{

	eqn_box(p, bp);
	p->flags &= ~TERMP_NOSPACE;
}