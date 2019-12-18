#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int anchor; int use; scalar_t__ restr; } ;
typedef  TYPE_1__ fa ;

/* Variables and functions */
 int MAXLIN ; 
 int NFA ; 
 scalar_t__ compile_time ; 
 TYPE_1__** fatab ; 
 int /*<<< orphan*/  freefa (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int maxsetvec ; 
 TYPE_1__* mkdfa (char const*,int) ; 
 int nfatab ; 
 int /*<<< orphan*/  overflo (char*) ; 
 int* setvec ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int* tmpset ; 

fa *makedfa(const char *s, int anchor)	/* returns dfa for reg expr s */
{
	int i, use, nuse;
	fa *pfa;
	static int now = 1;

	if (setvec == NULL) {	/* first time through any RE */
		maxsetvec = MAXLIN;
		setvec = (int *) malloc(maxsetvec * sizeof(int));
		tmpset = (int *) malloc(maxsetvec * sizeof(int));
		if (setvec == NULL || tmpset == NULL)
			overflo("out of space initializing makedfa");
	}

	if (compile_time)	/* a constant for sure */
		return mkdfa(s, anchor);
	for (i = 0; i < nfatab; i++)	/* is it there already? */
		if (fatab[i]->anchor == anchor
		  && strcmp((const char *) fatab[i]->restr, s) == 0) {
			fatab[i]->use = now++;
			return fatab[i];
		}
	pfa = mkdfa(s, anchor);
	if (nfatab < NFA) {	/* room for another */
		fatab[nfatab] = pfa;
		fatab[nfatab]->use = now++;
		nfatab++;
		return pfa;
	}
	use = fatab[0]->use;	/* replace least-recently used */
	nuse = 0;
	for (i = 1; i < nfatab; i++)
		if (fatab[i]->use < use) {
			use = fatab[i]->use;
			nuse = i;
		}
	freefa(fatab[nuse]);
	fatab[nuse] = pfa;
	pfa->use = now++;
	return pfa;
}