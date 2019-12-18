#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Term ;
struct TYPE_4__ {struct TYPE_4__* link; } ;
typedef  int /*<<< orphan*/  Nonterm ;

/* Variables and functions */
 int /*<<< orphan*/  emitcase (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print (char*,...) ; 

__attribute__((used)) static void emitlabel(Term terms, Nonterm start, int ntnumber) {
	int i;
	Term p;

	print("static void %Plabel(NODEPTR_TYPE a) {\n%1int c;\n"
"%1struct %Pstate *p;\n\n"
"%1if (!a)\n%2fatal(\"%Plabel\", \"Null tree\\n\", 0);\n");
	print("%1STATE_LABEL(a) = p = allocate(sizeof *p, FUNC);\n"
"%1p->rule._stmt = 0;\n");
	for (i = 1; i <= ntnumber; i++)
		print("%1p->cost[%d] =\n", i);
	print("%20x7fff;\n%1switch (OP_LABEL(a)) {\n");
	for (p = terms; p; p = p->link)
		emitcase(p, ntnumber);
	print("%1default:\n"
"%2fatal(\"%Plabel\", \"Bad terminal %%d\\n\", OP_LABEL(a));\n%1}\n}\n\n");
}