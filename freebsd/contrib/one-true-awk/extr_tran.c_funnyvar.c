#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tval; int /*<<< orphan*/  fval; int /*<<< orphan*/  sval; int /*<<< orphan*/  nval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char const*,int /*<<< orphan*/ ) ; 
 int FCN ; 
 int /*<<< orphan*/  WARNING (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isarr (TYPE_1__*) ; 

void funnyvar(Cell *vp, const char *rw)
{
	if (isarr(vp))
		FATAL("can't %s %s; it's an array name.", rw, vp->nval);
	if (vp->tval & FCN)
		FATAL("can't %s %s; it's a function.", rw, vp->nval);
	WARNING("funny variable %p: n=%s s=\"%s\" f=%g t=%o",
		vp, vp->nval, vp->sval, vp->fval, vp->tval);
}