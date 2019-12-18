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
typedef  scalar_t__ relation ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ declaration ;

/* Variables and functions */
 int PUT ; 
 scalar_t__ REL_ALIAS ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  tabify (int /*<<< orphan*/ ,int) ; 
 char* upcase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_single_in_line(int indent, declaration *decl, int flag, relation rel)
{
	char *upp_case;

	tabify(fout, indent);
	if (flag == PUT)
		f_print(fout, "IXDR_PUT_");
	else
		if (rel == REL_ALIAS)
			f_print(fout, "objp->%s = IXDR_GET_", decl->name);
		else
			f_print(fout, "*genp++ = IXDR_GET_");

	upp_case = upcase(decl->type);

	/* hack	 - XX */
	if (strcmp(upp_case, "INT") == 0)
	{
		free(upp_case);
		upp_case = strdup("LONG");
	}

	if (strcmp(upp_case, "U_INT") == 0)
	{
		free(upp_case);
		upp_case = strdup("U_LONG");
	}
	if (flag == PUT)
		if (rel == REL_ALIAS)
			f_print(fout,
				"%s(buf, objp->%s);\n", upp_case, decl->name);
		else
			f_print(fout, "%s(buf, *genp++);\n", upp_case);

	else
		f_print(fout, "%s(buf);\n", upp_case);
	free(upp_case);
}