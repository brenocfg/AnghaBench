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
struct assignment {int /*<<< orphan*/  name; struct assignment* next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct assignment *
find_next(struct assignment *as, const char *name)
{
    for(as = as->next; as != NULL; as = as->next) {
	if(strcmp(as->name, name) == 0)
	    return as;
    }
    return NULL;
}