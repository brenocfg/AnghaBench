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
struct TYPE_3__ {int /*<<< orphan*/  tval; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/ * CONVFMT ; 
 int /*<<< orphan*/  DONTFREE ; 
 int /*<<< orphan*/ * FILENAME ; 
 int /*<<< orphan*/ * FS ; 
 int /*<<< orphan*/ * OFMT ; 
 int /*<<< orphan*/ * OFS ; 
 int /*<<< orphan*/ * ORS ; 
 int /*<<< orphan*/ * RS ; 
 int /*<<< orphan*/ * SUBSEP ; 

__attribute__((used)) static void
setfree(Cell *vp)
{
	if (&vp->sval == FS || &vp->sval == RS ||
	    &vp->sval == OFS || &vp->sval == ORS ||
	    &vp->sval == OFMT || &vp->sval == CONVFMT ||
	    &vp->sval == FILENAME || &vp->sval == SUBSEP)
		vp->tval |= DONTFREE;
	else
		vp->tval &= ~DONTFREE;
}