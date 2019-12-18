#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  assignment; } ;
struct assignment {TYPE_1__ u; struct assignment* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  cprint (int,char*,...) ; 
 int /*<<< orphan*/  gen_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_wrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hname ; 
 int /*<<< orphan*/  hprint (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
gen(struct assignment *as)
{
    struct assignment *a;
    cprint(0, "#include <stdio.h>\n");
    cprint(0, "#include <getarg.h>\n");
    cprint(0, "#include <sl.h>\n");
    cprint(0, "#include \"%s\"\n\n", hname);

    hprint(0, "#include <stdio.h>\n");
    hprint(0, "#include <sl.h>\n");
    hprint(0, "\n");


    for(a = as; a != NULL; a = a->next)
	gen_wrapper(a->u.assignment);

    cprint(0, "SL_cmd commands[] = {\n");
    for(a = as; a != NULL; a = a->next)
	gen_command(a->u.assignment);
    cprint(1, "{ NULL }\n");
    cprint(0, "};\n");

    hprint(0, "extern SL_cmd commands[];\n");
}