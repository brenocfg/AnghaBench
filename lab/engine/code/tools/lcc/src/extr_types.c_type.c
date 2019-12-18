#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* sym; } ;
struct TYPE_4__ {int op; scalar_t__ type; int size; int align; TYPE_1__ u; } ;
struct entry {TYPE_2__ type; struct entry* link; } ;
typedef  scalar_t__ Type ;

/* Variables and functions */
 int ARRAY ; 
 int FUNCTION ; 
 int NELEMS (struct entry**) ; 
 int /*<<< orphan*/  NEW0 (struct entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 struct entry** typetable ; 

__attribute__((used)) static Type type(int op, Type ty, int size, int align, void *sym) {
	unsigned h = (op^((unsigned long)ty>>3))
&(NELEMS(typetable)-1);
	struct entry *tn;

	if (op != FUNCTION && (op != ARRAY || size > 0))
		for (tn = typetable[h]; tn; tn = tn->link)
			if (tn->type.op    == op   && tn->type.type  == ty
			&&  tn->type.size  == size && tn->type.align == align
			&&  tn->type.u.sym == sym)
				return &tn->type;
	NEW0(tn, PERM);
	tn->type.op = op;
	tn->type.type = ty;
	tn->type.size = size;
	tn->type.align = align;
	tn->type.u.sym = sym;
	tn->link = typetable[h];
	typetable[h] = tn;
	return &tn->type;
}