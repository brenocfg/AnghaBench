#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_28__ ;
typedef  struct TYPE_42__   TYPE_27__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ Type ;
typedef  TYPE_8__* Tree ;
struct TYPE_46__ {TYPE_3__* sym; } ;
struct TYPE_51__ {scalar_t__ type; TYPE_4__ u; } ;
struct TYPE_47__ {long i; } ;
struct TYPE_49__ {TYPE_27__* sym; TYPE_28__* field; TYPE_5__ v; } ;
struct TYPE_50__ {scalar_t__ type; scalar_t__ op; TYPE_7__ u; TYPE_6__** kids; } ;
struct TYPE_48__ {TYPE_8__** kids; } ;
struct TYPE_40__ {scalar_t__ cfields; } ;
struct TYPE_44__ {TYPE_1__ s; } ;
struct TYPE_45__ {TYPE_2__ u; } ;
struct TYPE_43__ {TYPE_24__* type; } ;
struct TYPE_42__ {int /*<<< orphan*/  name; int /*<<< orphan*/  generated; int /*<<< orphan*/  computed; } ;
struct TYPE_41__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASGN ; 
 scalar_t__ B ; 
 int /*<<< orphan*/  BAND ; 
 scalar_t__ CALL ; 
 scalar_t__ CNST ; 
 scalar_t__ FIELD ; 
 scalar_t__ I ; 
 int /*<<< orphan*/  LSH ; 
 scalar_t__ RIGHT ; 
 int /*<<< orphan*/  RSH ; 
 scalar_t__ assign (scalar_t__,TYPE_8__*) ; 
 TYPE_8__* bittree (int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 TYPE_8__* cast (TYPE_8__*,scalar_t__) ; 
 TYPE_8__* cnsttree (scalar_t__,long) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ fieldmask (TYPE_28__*) ; 
 unsigned long fieldsize (TYPE_28__*) ; 
 TYPE_8__* idtree (TYPE_27__*) ; 
 scalar_t__ inttype ; 
 scalar_t__ isaddrop (scalar_t__) ; 
 scalar_t__ iscallb (TYPE_8__*) ; 
 scalar_t__ isconst (scalar_t__) ; 
 scalar_t__ isptr (scalar_t__) ; 
 scalar_t__ isstruct (scalar_t__) ; 
 scalar_t__ isunsigned (TYPE_24__*) ; 
 TYPE_8__* lvalue (TYPE_8__*) ; 
 scalar_t__ mkop (int,scalar_t__) ; 
 TYPE_8__* pointer (TYPE_8__*) ; 
 TYPE_8__* retype (TYPE_8__*,scalar_t__) ; 
 TYPE_8__* shtree (int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 TYPE_8__* tree (scalar_t__,scalar_t__,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  typeerror (int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 TYPE_9__* unqual (scalar_t__) ; 
 scalar_t__ voidtype ; 

Tree asgntree(int op, Tree l, Tree r) {
	Type aty, ty;

	r = pointer(r);
	ty = assign(l->type, r);
	if (ty)
		r = cast(r, ty);
	else {
		typeerror(ASGN, l, r);
		if (r->type == voidtype)
			r = retype(r, inttype);
		ty = r->type;
	}
	if (l->op != FIELD)
		l = lvalue(l);
	aty = l->type;
	if (isptr(aty))
		aty = unqual(aty)->type;
	if ( isconst(aty)
	||  (isstruct(aty) && unqual(aty)->u.sym->u.s.cfields)) {
		if (isaddrop(l->op)
		&& !l->u.sym->computed && !l->u.sym->generated)
			error("assignment to const identifier `%s'\n",
				l->u.sym->name);
		else
			error("assignment to const location\n");
	}
	if (l->op == FIELD) {
		long n = 8*l->u.field->type->size - fieldsize(l->u.field);
		if (n > 0 && isunsigned(l->u.field->type))
			r = bittree(BAND, r,
				cnsttree(r->type, (unsigned long)fieldmask(l->u.field)));
		else if (n > 0) {
			if (r->op == CNST+I) {
				n = r->u.v.i;
				if (n&(1<<(fieldsize(l->u.field)-1)))
					n |= ~0UL<<fieldsize(l->u.field);
				r = cnsttree(r->type, n);
			} else
				r = shtree(RSH,
					shtree(LSH, r, cnsttree(inttype, n)),
					cnsttree(inttype, n));
		}
	}
	if (isstruct(ty) && isaddrop(l->op) && iscallb(r))
		return tree(RIGHT, ty,
			tree(CALL+B, ty, r->kids[0]->kids[0], l),
			idtree(l->u.sym));
	return tree(mkop(op,ty), ty, l, r);
}