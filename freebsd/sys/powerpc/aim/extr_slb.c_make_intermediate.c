#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {struct slbtnode** ua_child; } ;
struct slbtnode {int ua_level; scalar_t__ ua_base; int /*<<< orphan*/  ua_alloc; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ esid2base (scalar_t__,int) ; 
 int esid2idx (scalar_t__,int) ; 
 int /*<<< orphan*/  powerpc_lwsync () ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slbt_zone ; 
 struct slbtnode* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct slbtnode*
make_intermediate(uint64_t esid, struct slbtnode *parent)
{
	struct slbtnode *child, *inter;
	int idx, level;

	idx = esid2idx(esid, parent->ua_level);
	child = parent->u.ua_child[idx];
	KASSERT(esid2base(esid, child->ua_level) != child->ua_base,
	    ("No need for an intermediate node?"));

	/*
	 * Find the level where the existing child and our new esid
	 * meet.  It must be lower than parent->ua_level or we would
	 * have chosen a different index in parent.
	 */
	level = child->ua_level + 1;
	while (esid2base(esid, level) !=
	    esid2base(child->ua_base, level))
		level++;
	KASSERT(level < parent->ua_level,
	    ("Found splitting level %d for %09jx and %09jx, "
	    "but it's the same as %p's",
	    level, esid, child->ua_base, parent));

	/* unlock and M_WAITOK and loop? */
	inter = uma_zalloc(slbt_zone, M_NOWAIT | M_ZERO);
	KASSERT(inter != NULL, ("unhandled NULL case"));

	/* Set up intermediate node to point to child ... */
	inter->ua_level = level;
	inter->ua_base = esid2base(esid, inter->ua_level);
	idx = esid2idx(child->ua_base, inter->ua_level);
	inter->u.ua_child[idx] = child;
	setbit(&inter->ua_alloc, idx);
	powerpc_lwsync();

	/* Set up parent to point to intermediate node ... */
	idx = esid2idx(inter->ua_base, parent->ua_level);
	parent->u.ua_child[idx] = inter;
	setbit(&parent->ua_alloc, idx);

	return (inter);
}