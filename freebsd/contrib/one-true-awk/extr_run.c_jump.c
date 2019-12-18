#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int tval; scalar_t__ fval; } ;
struct TYPE_16__ {int tval; } ;
struct TYPE_15__ {TYPE_3__* retval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
#define  BREAK 133 
#define  CONTINUE 132 
#define  EXIT 131 
 int /*<<< orphan*/  FATAL (char*,int) ; 
#define  NEXT 130 
#define  NEXTFILE 129 
 int NUM ; 
#define  RETURN 128 
 int STR ; 
 int /*<<< orphan*/  env ; 
 int errorflag ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 TYPE_13__* fp ; 
 scalar_t__ getfval (TYPE_1__*) ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 TYPE_1__* jbreak ; 
 TYPE_1__* jcont ; 
 TYPE_1__* jnext ; 
 TYPE_1__* jnextfile ; 
 TYPE_1__* jret ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nextfile () ; 
 int /*<<< orphan*/  setfval (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  setsval (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *jump(Node **a, int n)	/* break, continue, next, nextfile, return */
{
	Cell *y;

	switch (n) {
	case EXIT:
		if (a[0] != NULL) {
			y = execute(a[0]);
			errorflag = (int) getfval(y);
			tempfree(y);
		}
		longjmp(env, 1);
	case RETURN:
		if (a[0] != NULL) {
			y = execute(a[0]);
			if ((y->tval & (STR|NUM)) == (STR|NUM)) {
				setsval(fp->retval, getsval(y));
				fp->retval->fval = getfval(y);
				fp->retval->tval |= NUM;
			}
			else if (y->tval & STR)
				setsval(fp->retval, getsval(y));
			else if (y->tval & NUM)
				setfval(fp->retval, getfval(y));
			else		/* can't happen */
				FATAL("bad type variable %d", y->tval);
			tempfree(y);
		}
		return(jret);
	case NEXT:
		return(jnext);
	case NEXTFILE:
		nextfile();
		return(jnextfile);
	case BREAK:
		return(jbreak);
	case CONTINUE:
		return(jcont);
	default:	/* can't happen */
		FATAL("illegal jump type %d", n);
	}
	return 0;	/* not reached */
}