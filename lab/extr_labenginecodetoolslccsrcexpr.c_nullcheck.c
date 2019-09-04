#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
struct TYPE_21__ {int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int /*<<< orphan*/  loc; } ;
struct TYPE_20__ {TYPE_1__ c; } ;
struct TYPE_18__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  OR ; 
 int /*<<< orphan*/  REGISTER ; 
 int /*<<< orphan*/  RIGHT ; 
 TYPE_4__* YYnull ; 
 int /*<<< orphan*/  asgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cast (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnsttree (int /*<<< orphan*/ ,long) ; 
 TYPE_3__* cond (int /*<<< orphan*/ ) ; 
 scalar_t__* file ; 
 int /*<<< orphan*/  idtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 scalar_t__ isptr (int /*<<< orphan*/ ) ; 
 scalar_t__ lineno ; 
 TYPE_14__* mkstr (scalar_t__*) ; 
 int /*<<< orphan*/  needconst ; 
 TYPE_3__* nullcall (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* value (TYPE_3__*) ; 
 int /*<<< orphan*/  vcall (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  voidptype ; 
 int /*<<< orphan*/  voidtype ; 

__attribute__((used)) static Tree nullcheck(Tree p) {
	if (!needconst && YYnull && isptr(p->type)) {
		p = value(p);
		if (strcmp(YYnull->name, "_YYnull") == 0) {
			Symbol t1 = temporary(REGISTER, voidptype);
			p = tree(RIGHT, p->type,
				tree(OR, voidtype,
					cond(asgn(t1, cast(p, voidptype))),
					vcall(YYnull, voidtype,	(file && *file ? pointer(idtree(mkstr(file)->u.c.loc)) : cnsttree(voidptype, NULL)), cnsttree(inttype, (long)lineno)		, NULL)),
				idtree(t1));
		}

		else
			p = nullcall(p->type, YYnull, p, cnsttree(inttype, 0L));

	}
	return p;
}