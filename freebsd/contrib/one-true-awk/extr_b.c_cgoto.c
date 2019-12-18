#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int accept; int** posns; int curstat; int** gototab; int reset; int* out; TYPE_2__* re; } ;
typedef  TYPE_3__ fa ;
struct TYPE_5__ {scalar_t__ up; int /*<<< orphan*/  np; } ;
struct TYPE_6__ {int ltype; int* lfollow; TYPE_1__ lval; } ;

/* Variables and functions */
 int ALL ; 
 int CCL ; 
 int CHAR ; 
 int DOT ; 
 int EMPTYRE ; 
 int FINAL ; 
 int HAT ; 
 int NCCL ; 
 int NCHARS ; 
 int NSTATES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int maxsetvec ; 
 scalar_t__ member (int,char*) ; 
 int /*<<< orphan*/  overflo (char*) ; 
 int ptoi (int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (int*,int) ; 
 int setcnt ; 
 int* setvec ; 
 int* tmpset ; 
 int /*<<< orphan*/  xfree (int*) ; 

int cgoto(fa *f, int s, int c)
{
	int i, j, k;
	int *p, *q;

	assert(c == HAT || c < NCHARS);
	while (f->accept >= maxsetvec) {	/* guessing here! */
		maxsetvec *= 4;
		setvec = (int *) realloc(setvec, maxsetvec * sizeof(int));
		tmpset = (int *) realloc(tmpset, maxsetvec * sizeof(int));
		if (setvec == NULL || tmpset == NULL)
			overflo("out of space in cgoto()");
	}
	for (i = 0; i <= f->accept; i++)
		setvec[i] = 0;
	setcnt = 0;
	/* compute positions of gototab[s,c] into setvec */
	p = f->posns[s];
	for (i = 1; i <= *p; i++) {
		if ((k = f->re[p[i]].ltype) != FINAL) {
			if ((k == CHAR && c == ptoi(f->re[p[i]].lval.np))
			 || (k == DOT && c != 0 && c != HAT)
			 || (k == ALL && c != 0)
			 || (k == EMPTYRE && c != 0)
			 || (k == CCL && member(c, (char *) f->re[p[i]].lval.up))
			 || (k == NCCL && !member(c, (char *) f->re[p[i]].lval.up) && c != 0 && c != HAT)) {
				q = f->re[p[i]].lfollow;
				for (j = 1; j <= *q; j++) {
					if (q[j] >= maxsetvec) {
						maxsetvec *= 4;
						setvec = (int *) realloc(setvec, maxsetvec * sizeof(int));
						tmpset = (int *) realloc(tmpset, maxsetvec * sizeof(int));
						if (setvec == NULL || tmpset == NULL)
							overflo("cgoto overflow");
					}
					if (setvec[q[j]] == 0) {
						setcnt++;
						setvec[q[j]] = 1;
					}
				}
			}
		}
	}
	/* determine if setvec is a previous state */
	tmpset[0] = setcnt;
	j = 1;
	for (i = f->accept; i >= 0; i--)
		if (setvec[i]) {
			tmpset[j++] = i;
		}
	/* tmpset == previous state? */
	for (i = 1; i <= f->curstat; i++) {
		p = f->posns[i];
		if ((k = tmpset[0]) != p[0])
			goto different;
		for (j = 1; j <= k; j++)
			if (tmpset[j] != p[j])
				goto different;
		/* setvec is state i */
		f->gototab[s][c] = i;
		return i;
	  different:;
	}

	/* add tmpset to current set of states */
	if (f->curstat >= NSTATES-1) {
		f->curstat = 2;
		f->reset = 1;
		for (i = 2; i < NSTATES; i++)
			xfree(f->posns[i]);
	} else
		++(f->curstat);
	for (i = 0; i < NCHARS; i++)
		f->gototab[f->curstat][i] = 0;
	xfree(f->posns[f->curstat]);
	if ((p = (int *) calloc(setcnt+1, sizeof(int))) == NULL)
		overflo("out of space in cgoto");

	f->posns[f->curstat] = p;
	f->gototab[s][c] = f->curstat;
	for (i = 0; i <= setcnt; i++)
		p[i] = tmpset[i];
	if (setvec[f->accept])
		f->out[f->curstat] = 1;
	else
		f->out[f->curstat] = 0;
	return f->curstat;
}