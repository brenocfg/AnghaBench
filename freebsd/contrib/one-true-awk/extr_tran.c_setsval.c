#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tval; char* sval; int fval; int /*<<< orphan*/  nval; int /*<<< orphan*/ * fmt; } ;
typedef  TYPE_1__ Cell ;
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 int CONVC ; 
 int CONVO ; 
 int* NF ; 
 int /*<<< orphan*/  NN (int /*<<< orphan*/ ) ; 
 int NUM ; 
 int STR ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ donefld ; 
 int donerec ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ freeable (TYPE_1__*) ; 
 int /*<<< orphan*/  funnyvar (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  getfval (TYPE_1__*) ; 
 scalar_t__ isfld (TYPE_1__*) ; 
 scalar_t__ isrec (TYPE_1__*) ; 
 int /*<<< orphan*/  newfld (int) ; 
 TYPE_1__* ofsloc ; 
 int /*<<< orphan*/  recbld () ; 
 int /*<<< orphan*/  setfree (TYPE_1__*) ; 
 int /*<<< orphan*/  setlastfld (int /*<<< orphan*/ ) ; 
 char* tostring (char const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

char *setsval(Cell *vp, const char *s)	/* set string val of a Cell */
{
	char *t;
	int fldno;
	Awkfloat f;

	   dprintf( ("starting setsval %p: %s = \"%s\", t=%o, r,f=%d,%d\n", 
		(void*)vp, NN(vp->nval), s, vp->tval, donerec, donefld) );
	if ((vp->tval & (NUM | STR)) == 0)
		funnyvar(vp, "assign to");
	if (isfld(vp)) {
		donerec = 0;	/* mark $0 invalid */
		fldno = atoi(vp->nval);
		if (fldno > *NF)
			newfld(fldno);
		   dprintf( ("setting field %d to %s (%p)\n", fldno, s, (void *) s) );
	} else if (isrec(vp)) {
		donefld = 0;	/* mark $1... invalid */
		donerec = 1;
	} else if (vp == ofsloc) {
		if (donerec == 0)
			recbld();
	}
	t = s ? tostring(s) : tostring("");	/* in case it's self-assign */
	if (freeable(vp))
		xfree(vp->sval);
	vp->tval &= ~(NUM|CONVC|CONVO);
	vp->tval |= STR;
	vp->fmt = NULL;
	setfree(vp);
	   dprintf( ("setsval %p: %s = \"%s (%p) \", t=%o r,f=%d,%d\n", 
		(void*)vp, NN(vp->nval), t, (void *) t, vp->tval, donerec, donefld) );
	vp->sval = t;
	if (&vp->fval == NF) {
		donerec = 0;	/* mark $0 invalid */
		f = getfval(vp);
		setlastfld(f);
		dprintf( ("setting NF to %g\n", f) );
	}

	return(vp->sval);
}