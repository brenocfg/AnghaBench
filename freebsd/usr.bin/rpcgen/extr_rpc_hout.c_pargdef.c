#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* procs; struct TYPE_12__* next; } ;
typedef  TYPE_4__ version_list ;
struct TYPE_11__ {char* argname; TYPE_7__* decls; } ;
struct TYPE_13__ {int arg_num; TYPE_3__ args; struct TYPE_13__* next; } ;
typedef  TYPE_5__ proc_list ;
struct TYPE_9__ {TYPE_4__* versions; } ;
struct TYPE_10__ {TYPE_1__ pr; } ;
struct TYPE_14__ {TYPE_2__ def; } ;
typedef  TYPE_6__ definition ;
struct TYPE_15__ {int /*<<< orphan*/  decl; struct TYPE_15__* next; } ;
typedef  TYPE_7__ decl_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  newstyle ; 
 int /*<<< orphan*/  pdeclaration (char*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  storexdrfuncdecl (char*,int) ; 

__attribute__((used)) static void
pargdef(definition *def)
{
	decl_list *l;
	version_list *vers;
	char *name;
	proc_list *plist;


	for (vers = def->def.pr.versions; vers != NULL; vers = vers->next) {
			for (plist = vers->procs; plist != NULL;
			    plist = plist->next) {

				if (!newstyle || plist->arg_num < 2) {
					continue; /* old style or single args */
				}
				name = plist->args.argname;
				f_print(fout, "struct %s {\n", name);
				for (l = plist->args.decls;
				    l != NULL; l = l->next) {
					pdeclaration(name, &l->decl, 1,
						     ";\n");
				}
				f_print(fout, "};\n");
				f_print(fout, "typedef struct %s %s;\n",
					name, name);
				storexdrfuncdecl(name, 1);
				f_print(fout, "\n");
			}
		}
}