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
struct parse {TYPE_1__* g; } ;
struct branchc {scalar_t__ terminate; } ;
struct TYPE_2__ {int /*<<< orphan*/  neol; int /*<<< orphan*/  iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP (int) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OEOL ; 
 int /*<<< orphan*/  USEEOL ; 

__attribute__((used)) static void
p_bre_post_parse(struct parse *p, struct branchc *bc)
{

	/* Expression is terminating due to EOL token */
	if (bc->terminate) {
		DROP(1);
		EMIT(OEOL, 0);
		p->g->iflags |= USEEOL;
		p->g->neol++;
	}
}