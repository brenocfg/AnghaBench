#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct parse {scalar_t__ ssize; int /*<<< orphan*/ * stripdata; int /*<<< orphan*/ * strip; } ;
typedef  scalar_t__ sopno ;
typedef  int /*<<< orphan*/  sop ;
typedef  int /*<<< orphan*/  RCHAR_T ;

/* Variables and functions */
 scalar_t__ MEMLIMIT ; 
 scalar_t__ MEMSIZE (struct parse*) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
enlarge(struct parse *p, sopno size)
{
	sop *sp;
	RCHAR_T *dp;
	sopno osize;

	if (p->ssize >= size)
		return 1;

	osize = p->ssize;
	p->ssize = size;
	if (MEMSIZE(p) > MEMLIMIT)
		goto oomem;
	sp = realloc(p->strip, p->ssize * sizeof(sop));
	if (sp == NULL)
		goto oomem;
	p->strip = sp;
	dp = realloc(p->stripdata, p->ssize * sizeof(RCHAR_T));
	if (dp == NULL) {
oomem:
		p->ssize = osize;
		SETERROR(REG_ESPACE);
		return 0;
	}
	p->stripdata = dp;
	return 1;
}