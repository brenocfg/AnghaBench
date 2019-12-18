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
struct TYPE_4__ {int rel; int /*<<< orphan*/  array_max; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ declaration ;

/* Variables and functions */
#define  REL_ALIAS 129 
#define  REL_VECTOR 128 
 int /*<<< orphan*/  emit_single_in_line (int,TYPE_1__*,int,int const) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  tabify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emit_inline(int indent, declaration *decl, int flag)
{
	switch (decl->rel) {
	case  REL_ALIAS :
		emit_single_in_line(indent, decl, flag, REL_ALIAS);
		break;
	case REL_VECTOR :
		tabify(fout, indent);
		f_print(fout, "{\n");
		tabify(fout, indent + 1);
		f_print(fout, "%s *genp;\n\n", decl->type);
		tabify(fout, indent + 1);
		f_print(fout,
			"for (i = 0, genp = objp->%s;\n", decl->name);
		tabify(fout, indent + 2);
		f_print(fout, "i < %s; i++) {\n", decl->array_max);
		emit_single_in_line(indent + 2, decl, flag, REL_VECTOR);
		tabify(fout, indent + 1);
		f_print(fout, "}\n");
		tabify(fout, indent);
		f_print(fout, "}\n");
		break;
	default:
		break;
	}
}