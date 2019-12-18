#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  argname; TYPE_3__* decls; } ;
struct TYPE_7__ {int /*<<< orphan*/  res_type; int /*<<< orphan*/  res_prefix; TYPE_1__ args; } ;
typedef  TYPE_2__ proc_list ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
struct TYPE_8__ {TYPE_5__ decl; struct TYPE_8__* next; } ;
typedef  TYPE_3__ decl_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 int /*<<< orphan*/  newstyle ; 
 int /*<<< orphan*/  pdeclaration (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

void
printarglist(proc_list *proc, const char *result, const char *addargname,
    const char *addargtype)
{

	decl_list *l;

	if (!newstyle) {
		/* old style: always pass argument by reference */
		f_print(fout, "(");
		ptype(proc->args.decls->decl.prefix,
		      proc->args.decls->decl.type, 1);

		if (mtflag) {/* Generate result field */
			f_print(fout, "*argp, ");
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, "*%s, %s%s)\n",
				result, addargtype, addargname);
		} else
			f_print(fout, "*argp, %s%s)\n", addargtype, addargname);
	} else if (streq(proc->args.decls->decl.type, "void")) {
		/* newstyle, 0 argument */
		if (mtflag) {
			f_print(fout, "(");
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, "*%s, %s%s)\n",
				result, addargtype, addargname);
		} else
			f_print(fout, "(%s%s)\n", addargtype, addargname);
	} else {
		/* new style, 1 or multiple arguments */
		f_print(fout, "(");
		for (l = proc->args.decls; l != NULL; l = l->next) {
			pdeclaration(proc->args.argname, &l->decl, 0, ", ");
		}
		if (mtflag) {
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, "*%s, ", result);

		}
		f_print(fout, "%s%s)\n", addargtype, addargname);
	}
}