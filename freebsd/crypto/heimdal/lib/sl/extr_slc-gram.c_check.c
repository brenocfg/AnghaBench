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
struct assignment {char* name; int lineno; scalar_t__ type; TYPE_1__ u; struct assignment* next; } ;

/* Variables and functions */
 scalar_t__ a_assignment ; 
 scalar_t__ check_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
check(struct assignment *as)
{
    struct assignment *a;
    int ret = 0;
    for(a = as; a != NULL; a = a->next) {
	if(strcmp(a->name, "command")) {
	    fprintf(stderr, "unknown type %s line %d\n", a->name, a->lineno);
	    ret++;
	    continue;
	}
	if(a->type != a_assignment) {
	    fprintf(stderr, "bad command definition %s line %d\n", a->name, a->lineno);
	    ret++;
	    continue;
	}
	ret += check_command(a->u.assignment);
    }
    return ret;
}