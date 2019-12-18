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
struct parse {scalar_t__ error; int* pbegin; int* pend; int /*<<< orphan*/ * stripdata; int /*<<< orphan*/ * strip; } ;
typedef  int sopno ;
typedef  int /*<<< orphan*/  sop ;
typedef  int /*<<< orphan*/  RCHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,size_t) ; 
 int HERE () ; 
 int NPAREN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static void
doinsert(struct parse *p, sop op, size_t opnd, sopno pos)
{
	sopno sn;
	sop s;
	RCHAR_T d;
	int i;

	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	sn = HERE();
	EMIT(op, opnd);		/* do checks, ensure space */
	assert(HERE() == sn+1);
	s = p->strip[sn];
	d = p->stripdata[sn];

	/* adjust paren pointers */
	assert(pos > 0);
	for (i = 1; i < NPAREN; i++) {
		if (p->pbegin[i] >= pos) {
			p->pbegin[i]++;
		}
		if (p->pend[i] >= pos) {
			p->pend[i]++;
		}
	}

	memmove((char *)&p->strip[pos+1], (char *)&p->strip[pos],
						(HERE()-pos-1)*sizeof(sop));
	memmove((char *)&p->stripdata[pos+1], (char *)&p->stripdata[pos],
						(HERE()-pos-1)*sizeof(RCHAR_T));
	p->strip[pos] = s;
	p->stripdata[pos] = d;
}