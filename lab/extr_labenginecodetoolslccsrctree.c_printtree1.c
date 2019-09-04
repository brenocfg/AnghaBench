#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_1__* sym; int /*<<< orphan*/  v; TYPE_6__* field; } ;
struct TYPE_11__ {scalar_t__ op; int node; struct TYPE_11__** kids; TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CNST ; 
 scalar_t__ FIELD ; 
 int NELEMS (TYPE_3__**) ; 
 int fieldright (TYPE_6__*) ; 
 int /*<<< orphan*/  fieldsize (TYPE_6__*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ generic (scalar_t__) ; 
 int nodeid (TYPE_3__*) ; 
 int /*<<< orphan*/  opname (scalar_t__) ; 
 int* printed (int) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  vtoa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void printtree1(Tree p, int fd, int lev) {
	FILE *f = fd == 1 ? stdout : stderr;
	int i;
	static char blanks[] = "                                                   ";

	if (p == 0 || *printed(i = nodeid(p)))
		return;
	fprint(f, "#%d%S%S", i, blanks, i < 10 ? 2 : i < 100 ? 1 : 0, blanks, lev);
	fprint(f, "%s %t", opname(p->op), p->type);
	*printed(i) = 1;
	for (i = 0; i < NELEMS(p->kids); i++)
		if (p->kids[i])
			fprint(f, " #%d", nodeid(p->kids[i]));
	if (p->op == FIELD && p->u.field)
		fprint(f, " %s %d..%d", p->u.field->name,
			fieldsize(p->u.field) + fieldright(p->u.field), fieldright(p->u.field));
	else if (generic(p->op) == CNST)
		fprint(f, " %s", vtoa(p->type, p->u.v));
	else if (p->u.sym)
		fprint(f, " %s", p->u.sym->name);
	if (p->node)
		fprint(f, " node=%p", p->node);
	fprint(f, "\n");
	for (i = 0; i < NELEMS(p->kids); i++)
		printtree1(p->kids[i], fd, lev + 1);
}