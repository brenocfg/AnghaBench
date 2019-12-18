#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uch ;
struct parse {int ncsalloc; TYPE_1__* g; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/ * multis; scalar_t__ smultis; scalar_t__ hash; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_2__ cset ;
struct TYPE_4__ {int /*<<< orphan*/ * setbits; TYPE_2__* sets; int /*<<< orphan*/  csetsize; int /*<<< orphan*/  ncsets; } ;

/* Variables and functions */
 size_t CHAR_BIT ; 
 scalar_t__ MEMLIMIT ; 
 scalar_t__ MEMSIZE (struct parse*) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (size_t) ; 
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
		p->ncsalloc += CHAR_BIT;
		nc = p->ncsalloc;
		assert(nc % CHAR_BIT == 0);
		nbytes = nc / CHAR_BIT * css;
		if (MEMSIZE(p) > MEMLIMIT)
			goto oomem;
		if (p->g->sets == NULL)
			p->g->sets = (cset *)malloc(nc * sizeof(cset));
		else
			p->g->sets = (cset *)realloc((char *)p->g->sets,
							nc * sizeof(cset));
		if (p->g->setbits == NULL)
			p->g->setbits = (uch *)malloc(nbytes);
		else {
			p->g->setbits = (uch *)realloc((char *)p->g->setbits,
								nbytes);
			/* xxx this isn't right if setbits is now NULL */
			for (i = 0; i < no; i++)
				p->g->sets[i].ptr = p->g->setbits + css*(i/CHAR_BIT);
		}
		if (p->g->sets != NULL && p->g->setbits != NULL)
			memset((char *)p->g->setbits + (nbytes - css),
								0, css);
		else {
oomem:
			no = 0;
			SETERROR(REG_ESPACE);
			/* caller's responsibility not to do set ops */
			return NULL;
		}
	}

	cs = &p->g->sets[no];
	cs->ptr = p->g->setbits + css*((no)/CHAR_BIT);
	cs->mask = 1 << ((no) % CHAR_BIT);
	cs->hash = 0;
	cs->smultis = 0;
	cs->multis = NULL;

	return(cs);
}