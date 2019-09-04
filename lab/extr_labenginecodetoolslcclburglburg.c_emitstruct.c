#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lhscount; struct TYPE_3__* link; } ;
typedef  TYPE_1__* Nonterm ;

/* Variables and functions */
 int /*<<< orphan*/  print (char*,...) ; 

__attribute__((used)) static void emitstruct(Nonterm nts, int ntnumber) {
	print("struct %Pstate {\n%1short cost[%d];\n%1struct {\n", ntnumber + 1);
	for ( ; nts; nts = nts->link) {
		int n = 1, m = nts->lhscount;
		while ((m >>= 1) != 0)
			n++;		
		print("%2unsigned int %P%S:%d;\n", nts, n);
	}
	print("%1} rule;\n};\n\n");
}