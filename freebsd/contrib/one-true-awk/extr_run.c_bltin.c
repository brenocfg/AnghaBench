#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uschar ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_19__ {int nelem; } ;
struct TYPE_18__ {scalar_t__ sval; } ;
struct TYPE_17__ {struct TYPE_17__* nnext; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ Cell ;
typedef  int Awkfloat ;
typedef  TYPE_3__ Array ;

/* Variables and functions */
 int EOF ; 
#define  FAND 147 
 int /*<<< orphan*/  FATAL (char*,int) ; 
#define  FATAN 146 
#define  FCOMPL 145 
#define  FCOS 144 
#define  FEXP 143 
#define  FFLUSH 142 
#define  FFOR 141 
#define  FINT 140 
#define  FLENGTH 139 
#define  FLOG 138 
#define  FLSHIFT 137 
#define  FRAND 136 
#define  FRSHIFT 135 
#define  FSIN 134 
#define  FSQRT 133 
#define  FSRAND 132 
#define  FSYSTEM 131 
#define  FTOLOWER 130 
#define  FTOUPPER 129 
#define  FXOR 128 
 int /*<<< orphan*/  WARNING (char*) ; 
 int /*<<< orphan*/  WCOREDUMP (int) ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int atan2 (int,int) ; 
 int cos (int) ; 
 int errcheck (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* execute (TYPE_1__*) ; 
 int /*<<< orphan*/  exp (int) ; 
 int fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getfval (TYPE_2__*) ; 
 int /*<<< orphan*/  getsval (TYPE_2__*) ; 
 TYPE_2__* gettemp () ; 
 int /*<<< orphan*/  isarr (TYPE_2__*) ; 
 int /*<<< orphan*/  islower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isrec (TYPE_2__*) ; 
 int /*<<< orphan*/  isupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int) ; 
 int /*<<< orphan*/  modf (int,int*) ; 
 int /*<<< orphan*/ * openfile (int const,int /*<<< orphan*/ ) ; 
 int ptoi (TYPE_1__*) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  setfval (TYPE_2__*,int) ; 
 int /*<<< orphan*/  setsval (TYPE_2__*,char*) ; 
 int sin (int) ; 
 int /*<<< orphan*/  sqrt (int) ; 
 int srand_seed ; 
 int /*<<< orphan*/  srandom (unsigned long) ; 
 int /*<<< orphan*/ * stdout ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (TYPE_2__*) ; 
 int time (int /*<<< orphan*/ *) ; 
 char tolower (int /*<<< orphan*/ ) ; 
 char* tostring (int /*<<< orphan*/ ) ; 
 char toupper (int /*<<< orphan*/ ) ; 

Cell *bltin(Node **a, int n)	/* builtin functions. a[0] is type, a[1] is arg list */
{
	Cell *x, *y;
	Awkfloat u;
	int t, i;
	Awkfloat tmp;
	char *p, *buf;
	Node *nextarg;
	FILE *fp;
	void flush_all(void);
	int status = 0;

	t = ptoi(a[0]);
	x = execute(a[1]);
	nextarg = a[1]->nnext;
	switch (t) {
	case FLENGTH:
		if (isarr(x))
			u = ((Array *) x->sval)->nelem;	/* GROT.  should be function*/
		else
			u = strlen(getsval(x));
		break;
	case FLOG:
		u = errcheck(log(getfval(x)), "log"); break;
	case FINT:
		modf(getfval(x), &u); break;
	case FEXP:
		u = errcheck(exp(getfval(x)), "exp"); break;
	case FSQRT:
		u = errcheck(sqrt(getfval(x)), "sqrt"); break;
	case FSIN:
		u = sin(getfval(x)); break;
	case FCOS:
		u = cos(getfval(x)); break;
	case FATAN:
		if (nextarg == NULL) {
			WARNING("atan2 requires two arguments; returning 1.0");
			u = 1.0;
		} else {
			y = execute(a[1]->nnext);
			u = atan2(getfval(x), getfval(y));
			tempfree(y);
			nextarg = nextarg->nnext;
		}
		break;
	case FCOMPL:
		u = ~((int)getfval(x));
		break;
	case FAND:
		if (nextarg == NULL) {
			WARNING("and requires two arguments; returning 0");
			u = 0;
			break;
		}
		i = ((int)getfval(x));
		while (nextarg != NULL) {
			y = execute(nextarg);
			i &= (int)getfval(y);
			tempfree(y);
			nextarg = nextarg->nnext;
		}
		u = i;
		break;
	case FFOR:
		if (nextarg == NULL) {
			WARNING("or requires two arguments; returning 0");
			u = 0;
			break;
		}
		i = ((int)getfval(x));
		while (nextarg != NULL) {
			y = execute(nextarg);
			i |= (int)getfval(y);
			tempfree(y);
			nextarg = nextarg->nnext;
		}
		u = i;
		break;
	case FXOR:
		if (nextarg == NULL) {
			WARNING("xor requires two arguments; returning 0");
			u = 0;
			break;
		}
		i = ((int)getfval(x));
		while (nextarg != NULL) {
			y = execute(nextarg);
			i ^= (int)getfval(y);
			tempfree(y);
			nextarg = nextarg->nnext;
		}
		u = i;
		break;
	case FLSHIFT:
		if (nextarg == NULL) {
			WARNING("lshift requires two arguments; returning 0");
			u = 0;
			break;
		}
		y = execute(a[1]->nnext);
		u = ((int)getfval(x)) << ((int)getfval(y));
		tempfree(y);
		nextarg = nextarg->nnext;
		break;
	case FRSHIFT:
		if (nextarg == NULL) {
			WARNING("rshift requires two arguments; returning 0");
			u = 0;
			break;
		}
		y = execute(a[1]->nnext);
		u = ((int)getfval(x)) >> ((int)getfval(y));
		tempfree(y);
		nextarg = nextarg->nnext;
		break;
	case FSYSTEM:
		fflush(stdout);		/* in case something is buffered already */
		status = system(getsval(x));
		u = status;
		if (status != -1) {
			if (WIFEXITED(status)) {
				u = WEXITSTATUS(status);
			} else if (WIFSIGNALED(status)) {
				u = WTERMSIG(status) + 256;
#ifdef WCOREDUMP
				if (WCOREDUMP(status))
					u += 256;
#endif
			} else	/* something else?!? */
				u = 0;
		}
		break;
	case FRAND:
		/* random() returns numbers in [0..2^31-1]
		 * in order to get a number in [0, 1), divide it by 2^31
		 */
		u = (Awkfloat) random() / (0x7fffffffL + 0x1UL);
		break;
	case FSRAND:
		if (isrec(x))	/* no argument provided */
			u = time((time_t *)0);
		else
			u = getfval(x);
		tmp = u;
		srandom((unsigned long) u);
		u = srand_seed;
		srand_seed = tmp;
		break;
	case FTOUPPER:
	case FTOLOWER:
		buf = tostring(getsval(x));
		if (t == FTOUPPER) {
			for (p = buf; *p; p++)
				if (islower((uschar) *p))
					*p = toupper((uschar)*p);
		} else {
			for (p = buf; *p; p++)
				if (isupper((uschar) *p))
					*p = tolower((uschar)*p);
		}
		tempfree(x);
		x = gettemp();
		setsval(x, buf);
		free(buf);
		return x;
	case FFLUSH:
		if (isrec(x) || strlen(getsval(x)) == 0) {
			flush_all();	/* fflush() or fflush("") -> all */
			u = 0;
		} else if ((fp = openfile(FFLUSH, getsval(x))) == NULL)
			u = EOF;
		else
			u = fflush(fp);
		break;
	default:	/* can't happen */
		FATAL("illegal function type %d", t);
		break;
	}
	tempfree(x);
	x = gettemp();
	setfval(x, u);
	if (nextarg != NULL) {
		WARNING("warning: function has too many arguments");
		for ( ; nextarg; nextarg = nextarg->nnext)
			execute(nextarg);
	}
	return(x);
}