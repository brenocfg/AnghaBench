#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int tval; int /*<<< orphan*/  fval; int /*<<< orphan*/  nval; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Cell ;
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 int CON ; 
 int /*<<< orphan*/  NN (int /*<<< orphan*/ ) ; 
 int NUM ; 
 int STR ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 scalar_t__ donefld ; 
 scalar_t__ donerec ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  fldbld () ; 
 int /*<<< orphan*/  funnyvar (TYPE_1__*,char*) ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ isfld (TYPE_1__*) ; 
 int /*<<< orphan*/  isnum (TYPE_1__*) ; 
 scalar_t__ isrec (TYPE_1__*) ; 
 int /*<<< orphan*/  recbld () ; 

Awkfloat getfval(Cell *vp)	/* get float val of a Cell */
{
	if ((vp->tval & (NUM | STR)) == 0)
		funnyvar(vp, "read value of");
	if (isfld(vp) && donefld == 0)
		fldbld();
	else if (isrec(vp) && donerec == 0)
		recbld();
	if (!isnum(vp)) {	/* not a number */
		vp->fval = atof(vp->sval);	/* best guess */
		if (is_number(vp->sval) && !(vp->tval&CON))
			vp->tval |= NUM;	/* make NUM only sparingly */
	}
	   dprintf( ("getfval %p: %s = %g, t=%o\n",
		(void*)vp, NN(vp->nval), vp->fval, vp->tval) );
	return(vp->fval);
}