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
struct TYPE_5__ {struct TYPE_5__* link; TYPE_1__* rules; } ;
struct TYPE_4__ {int /*<<< orphan*/  ern; struct TYPE_4__* decode; } ;
typedef  TYPE_1__* Rule ;
typedef  TYPE_2__* Nonterm ;

/* Variables and functions */
 int /*<<< orphan*/  ntnumber ; 
 int /*<<< orphan*/  print (char*,...) ; 

__attribute__((used)) static void emitrule(Nonterm nts) {
	Nonterm p;

	for (p = nts; p; p = p->link) {
		Rule r;
		print("static short %Pdecode_%S[] = {\n%10,\n", p);
		for (r = p->rules; r; r = r->decode)
			print("%1%d,\n", r->ern);
		print("};\n\n");
	}
	print("static int %Prule(void *state, int goalnt) {\n"
"%1if (goalnt < 1 || goalnt > %d)\n%2fatal(\"%Prule\", \"Bad goal nonterminal %%d\\n\", goalnt);\n"
"%1if (!state)\n%2return 0;\n%1switch (goalnt) {\n", ntnumber);
	for (p = nts; p; p = p->link)
		print("%1case %P%S_NT:"
"%1return %Pdecode_%S[((struct %Pstate *)state)->rule.%P%S];\n", p, p, p);
	print("%1default:\n%2fatal(\"%Prule\", \"Bad goal nonterminal %%d\\n\", goalnt);\n%2return 0;\n%1}\n}\n\n");
}