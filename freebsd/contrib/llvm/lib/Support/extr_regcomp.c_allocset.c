#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uch ;
struct parse {int ncsalloc; TYPE_1__* g; } ;
struct TYPE_6__ {int mask; int /*<<< orphan*/ * multis; scalar_t__ smultis; scalar_t__ hash; struct TYPE_6__* ptr; } ;
typedef  TYPE_2__ cset ;
struct TYPE_5__ {TYPE_2__* setbits; TYPE_2__* sets; int /*<<< orphan*/  csetsize; int /*<<< orphan*/  ncsets; } ;

/* Variables and functions */
 size_t CHAR_BIT ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ realloc (char*,size_t) ; 

__attribute__((used)) static cset *
allocset(struct parse *p)
{
	int no = p->g->ncsets++;
	size_t nc;
	size_t nbytes;
	cset *cs;
	size_t css = (size_t)p->g->csetsize;
	int i;

	if (no >= p->ncsalloc) {	/* need another column of space */
		void *ptr;

		p->ncsalloc += CHAR_BIT;
		nc = p->ncsalloc;
		if (nc > SIZE_MAX / sizeof(cset))
			goto nomem;
		assert(nc % CHAR_BIT == 0);
		nbytes = nc / CHAR_BIT * css;

		ptr = (cset *)realloc((char *)p->g->sets, nc * sizeof(cset));
		if (ptr == NULL)
			goto nomem;
		p->g->sets = ptr;

		ptr = (uch *)realloc((char *)p->g->setbits, nbytes);
		if (ptr == NULL)
			goto nomem;
		p->g->setbits = ptr;

		for (i = 0; i < no; i++)
			p->g->sets[i].ptr = p->g->setbits + css*(i/CHAR_BIT);

		(void) memset((char *)p->g->setbits + (nbytes - css), 0, css);
	}
	/* XXX should not happen */
	if (p->g->sets == NULL || p->g->setbits == NULL)
		goto nomem;

	cs = &p->g->sets[no];
	cs->ptr = p->g->setbits + css*((no)/CHAR_BIT);
	cs->mask = 1 << ((no) % CHAR_BIT);
	cs->hash = 0;
	cs->smultis = 0;
	cs->multis = NULL;

	return(cs);
nomem:
	free(p->g->sets);
	p->g->sets = NULL;
	free(p->g->setbits);
	p->g->setbits = NULL;

	SETERROR(REG_ESPACE);
	/* caller's responsibility not to do set ops */
	return(NULL);
}