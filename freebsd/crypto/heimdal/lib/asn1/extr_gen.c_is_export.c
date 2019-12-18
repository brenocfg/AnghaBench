#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sexport {int defined; int /*<<< orphan*/  name; struct sexport* next; } ;

/* Variables and functions */
 struct sexport* exports ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
is_export(const char *name)
{
    struct sexport *tmp;

    if (exports == NULL) /* no export list, all exported */
	return 1;

    for (tmp = exports; tmp != NULL; tmp = tmp->next) {
	if (strcmp(tmp->name, name) == 0) {
	    tmp->defined = 1;
	    return 1;
	}
    }
    return 0;
}