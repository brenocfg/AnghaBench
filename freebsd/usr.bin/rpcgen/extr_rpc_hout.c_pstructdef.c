#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* decls; } ;
struct TYPE_7__ {TYPE_1__ st; } ;
struct TYPE_8__ {char* def_name; TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;
struct TYPE_9__ {int /*<<< orphan*/  decl; struct TYPE_9__* next; } ;
typedef  TYPE_4__ decl_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  pdeclaration (char const*,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void
pstructdef(definition *def)
{
	decl_list *l;
	const char *name = def->def_name;

	f_print(fout, "struct %s {\n", name);
	for (l = def->def.st.decls; l != NULL; l = l->next) {
		pdeclaration(name, &l->decl, 1, ";\n");
	}
	f_print(fout, "};\n");
	f_print(fout, "typedef struct %s %s;\n", name, name);
}