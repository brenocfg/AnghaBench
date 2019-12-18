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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct assignment {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,...) ; 
 struct assignment* find (struct assignment*,char*) ; 
 int /*<<< orphan*/  gen_name (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
make_name(struct assignment *as)
{
    struct assignment *lopt;
    struct assignment *type;
    char *s;

    lopt = find(as, "long");
    if(lopt == NULL)
	lopt = find(as, "name");
    if(lopt == NULL)
	return NULL;

    type = find(as, "type");
    if(strcmp(type->u.value, "-flag") == 0)
	asprintf(&s, "%s_flag", lopt->u.value);
    else
	asprintf(&s, "%s_%s", lopt->u.value, type->u.value);
    gen_name(s);
    return s;
}