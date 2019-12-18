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
struct mparse {int /*<<< orphan*/  roff; TYPE_2__* man; } ;
struct TYPE_4__ {scalar_t__ macroset; } ;
struct TYPE_5__ {TYPE_1__ meta; } ;

/* Variables and functions */
 scalar_t__ MACROSET_MAN ; 
 scalar_t__ MACROSET_MDOC ; 
 scalar_t__ MACROSET_NONE ; 
 int /*<<< orphan*/  man_endparse (TYPE_2__*) ; 
 int /*<<< orphan*/  mdoc_endparse (TYPE_2__*) ; 
 int /*<<< orphan*/  roff_endparse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mparse_end(struct mparse *curp)
{
	if (curp->man->meta.macroset == MACROSET_NONE)
		curp->man->meta.macroset = MACROSET_MAN;
	if (curp->man->meta.macroset == MACROSET_MDOC)
		mdoc_endparse(curp->man);
	else
		man_endparse(curp->man);
	roff_endparse(curp->roff);
}