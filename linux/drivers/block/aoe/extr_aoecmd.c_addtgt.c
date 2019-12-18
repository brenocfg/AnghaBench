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
typedef  int ulong ;
struct aoetgt {int nframes; int maxout; int /*<<< orphan*/  ffree; int /*<<< orphan*/  ifs; int /*<<< orphan*/  ifp; int /*<<< orphan*/  addr; struct aoedev* d; } ;
struct aoedev {int ntargets; struct aoetgt** targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aoecmd_wreset (struct aoetgt*) ; 
 struct aoetgt** grow_targets (struct aoedev*) ; 
 struct aoetgt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static struct aoetgt *
addtgt(struct aoedev *d, char *addr, ulong nframes)
{
	struct aoetgt *t, **tt, **te;

	tt = d->targets;
	te = tt + d->ntargets;
	for (; tt < te && *tt; tt++)
		;

	if (tt == te) {
		tt = grow_targets(d);
		if (!tt)
			goto nomem;
	}
	t = kzalloc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		goto nomem;
	t->nframes = nframes;
	t->d = d;
	memcpy(t->addr, addr, sizeof t->addr);
	t->ifp = t->ifs;
	aoecmd_wreset(t);
	t->maxout = t->nframes / 2;
	INIT_LIST_HEAD(&t->ffree);
	return *tt = t;

 nomem:
	pr_info("aoe: cannot allocate memory to add target\n");
	return NULL;
}