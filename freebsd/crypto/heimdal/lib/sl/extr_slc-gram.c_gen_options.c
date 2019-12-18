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
struct type_handler {int /*<<< orphan*/  c_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  assignment; } ;
struct assignment {TYPE_1__ u; } ;

/* Variables and functions */
 struct assignment* find (int /*<<< orphan*/ ,char*) ; 
 struct type_handler* find_handler (struct assignment*) ; 
 struct assignment* find_next (struct assignment*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hprint (int,char*,...) ; 
 char* make_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_options(struct assignment *opt1, const char *name)
{
    struct assignment *tmp;

    hprint(0, "struct %s_options {\n", name);

    for(tmp = opt1;
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	struct assignment *type;
	struct type_handler *th;
	char *s;

	s = make_name(tmp->u.assignment);
	type = find(tmp->u.assignment, "type");
	th = find_handler(type);
	hprint(1, "%s %s;\n", th->c_type, s);
	free(s);
    }
    hprint(0, "};\n");
}