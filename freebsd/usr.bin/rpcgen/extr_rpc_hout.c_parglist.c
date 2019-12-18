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
struct TYPE_8__ {int arg_num; int /*<<< orphan*/  res_type; int /*<<< orphan*/  res_prefix; TYPE_1__ args; } ;
typedef  TYPE_3__ proc_list ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
struct TYPE_9__ {TYPE_2__ decl; struct TYPE_9__* next; } ;
typedef  TYPE_4__ decl_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 scalar_t__ newstyle ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
parglist(proc_list *proc, const char *addargtype)
{
	decl_list *dl;

	f_print(fout, "(");
	if (proc->arg_num < 2 && newstyle &&
	    streq(proc->args.decls->decl.type, "void")) {
		/* 0 argument in new style:  do nothing*/
	}
	else {
		for (dl = proc->args.decls; dl != NULL; dl = dl->next) {
			ptype(dl->decl.prefix, dl->decl.type, 1);
			if (!newstyle)
				f_print(fout, "*");
			/* old style passes by reference */
			f_print(fout, ", ");
		}
	}

	if (mtflag)  {
		ptype(proc->res_prefix, proc->res_type, 1);
		f_print(fout, "*, ");
	}

	f_print(fout, "%s);\n", addargtype);

}