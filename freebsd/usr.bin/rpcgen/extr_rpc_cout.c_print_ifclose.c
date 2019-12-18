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

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  tabify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_ifclose(int indent, int brace)
{
	f_print(fout, "))\n");
	tabify(fout, indent);
	f_print(fout, "\treturn (FALSE);\n");
	if (brace)
		f_print(fout, "\t}\n");
}