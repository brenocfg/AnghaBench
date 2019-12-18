#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_4__* default_decl; TYPE_5__* cases; TYPE_6__ enum_decl; } ;
struct TYPE_9__ {TYPE_1__ un; } ;
struct TYPE_10__ {char const* def_name; TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;
struct TYPE_11__ {char const* name; int /*<<< orphan*/  array_max; int /*<<< orphan*/  rel; int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
typedef  TYPE_4__ declaration ;
struct TYPE_12__ {int contflag; TYPE_4__ case_decl; int /*<<< orphan*/  case_name; struct TYPE_12__* next; } ;
typedef  TYPE_5__ case_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isvectordef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_ifstat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  print_stat (int,TYPE_6__*) ; 
 int /*<<< orphan*/  s_print (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
emit_union(definition *def)
{
	declaration *dflt;
	case_list *cl;
	declaration *cs;
	char *object;
	const char *vecformat = "objp->%s_u.%s";
	const char *format = "&objp->%s_u.%s";

	print_stat(1, &def->def.un.enum_decl);
	f_print(fout, "\tswitch (objp->%s) {\n", def->def.un.enum_decl.name);
	for (cl = def->def.un.cases; cl != NULL; cl = cl->next) {

		f_print(fout, "\tcase %s:\n", cl->case_name);
		if (cl->contflag == 1) /* a continued case statement */
			continue;
		cs = &cl->case_decl;
		if (!streq(cs->type, "void")) {
			object = xmalloc(strlen(def->def_name) +
			                 strlen(format) + strlen(cs->name) + 1);
			if (isvectordef (cs->type, cs->rel)) {
				s_print(object, vecformat, def->def_name,
					cs->name);
			} else {
				s_print(object, format, def->def_name,
					cs->name);
			}
			print_ifstat(2, cs->prefix, cs->type, cs->rel,
				     cs->array_max, object, cs->name);
			free(object);
		}
		f_print(fout, "\t\tbreak;\n");
	}
	dflt = def->def.un.default_decl;
	if (dflt != NULL) {
		if (!streq(dflt->type, "void")) {
			f_print(fout, "\tdefault:\n");
			object = xmalloc(strlen(def->def_name) +
			                 strlen(format) + strlen(dflt->name) + 1);
			if (isvectordef (dflt->type, dflt->rel)) {
				s_print(object, vecformat, def->def_name,
					dflt->name);
			} else {
				s_print(object, format, def->def_name,
					dflt->name);
			}

			print_ifstat(2, dflt->prefix, dflt->type, dflt->rel,
				    dflt->array_max, object, dflt->name);
			free(object);
			f_print(fout, "\t\tbreak;\n");
		} else {
			f_print(fout, "\tdefault:\n");
			f_print(fout, "\t\tbreak;\n");
		}
	} else {
		f_print(fout, "\tdefault:\n");
		f_print(fout, "\t\treturn (FALSE);\n");
	}

	f_print(fout, "\t}\n");
}