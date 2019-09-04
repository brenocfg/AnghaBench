#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_5__** kids; } ;
struct TYPE_23__ {TYPE_3__ x; int /*<<< orphan*/ * kids; int /*<<< orphan*/  op; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_22__ {TYPE_1__ x; } ;
struct TYPE_20__ {int /*<<< orphan*/  size; } ;
struct TYPE_18__ {TYPE_2__ ptrmetric; } ;
typedef  TYPE_4__* Symbol ;
typedef  TYPE_5__* Node ;

/* Variables and functions */
 scalar_t__ ADDRL ; 
 scalar_t__ INDIR ; 
 TYPE_17__* IR ; 
 scalar_t__ P ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumptree (TYPE_5__*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  linearize (TYPE_5__*,TYPE_5__*) ; 
 void* newnode (scalar_t__,TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int opkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune (TYPE_5__*,TYPE_5__**) ; 
 int /*<<< orphan*/  reprune (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int /*<<< orphan*/  rewrite (TYPE_5__*) ; 
 scalar_t__ sizeop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void genreload(Node p, Symbol tmp, int i) {
	Node q;
	int ty;

	debug(fprint(stderr, "(replacing %x with a reload from %s)\n", p->x.kids[i], tmp->x.name));
	debug(fprint(stderr, "(genreload: "));
	debug(dumptree(p->x.kids[i]));
	debug(fprint(stderr, ")\n"));
	ty = opkind(p->x.kids[i]->op);
	q = newnode(ADDRL+P + sizeop(IR->ptrmetric.size), NULL, NULL, tmp);
	p->x.kids[i] = newnode(INDIR + ty, q, NULL, NULL);
	rewrite(p->x.kids[i]);
	prune(p->x.kids[i], &q);
	reprune(&p->kids[1], reprune(&p->kids[0], 0, i, p), i, p);
	prune(p, &q);
	linearize(p->x.kids[i], p);
}