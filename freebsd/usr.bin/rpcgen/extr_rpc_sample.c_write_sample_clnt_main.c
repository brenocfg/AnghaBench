#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vers_num; struct TYPE_9__* next; } ;
typedef  TYPE_3__ version_list ;
struct TYPE_10__ {TYPE_5__* val; struct TYPE_10__* next; } ;
typedef  TYPE_4__ list ;
struct TYPE_7__ {TYPE_3__* versions; } ;
struct TYPE_8__ {TYPE_1__ pr; } ;
struct TYPE_11__ {scalar_t__ def_kind; int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_5__ definition ;

/* Variables and functions */
 scalar_t__ DEF_PROGRAM ; 
 TYPE_4__* defined ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  pvname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
write_sample_clnt_main(void)
{
	list *l;
	definition *def;
	version_list *vp;

	f_print(fout, "\n\n");
	f_print(fout, "int\n");
	f_print(fout, "main(int argc, char *argv[])\n{\n");

	f_print(fout, "\tchar *host;");
	f_print(fout, "\n\n\tif (argc < 2) {");
	f_print(fout, "\n\t\tprintf(\"usage:  %%s server_host\\n\", argv[0]);\n");
	f_print(fout, "\t\texit(1);\n\t}");
	f_print(fout, "\n\thost = argv[1];\n");

	for (l = defined; l != NULL; l = l->next) {
		def = l->val;
		if (def->def_kind != DEF_PROGRAM) {
			continue;
		}
		for (vp = def->def.pr.versions; vp != NULL; vp = vp->next) {
		        f_print(fout, "\t");
			pvname(def->def_name, vp->vers_num);
			f_print(fout, "(host);\n");
		}
	}
	f_print(fout, "}\n");
}