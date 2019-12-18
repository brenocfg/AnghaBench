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
typedef  TYPE_1__* properties ;
struct TYPE_3__ {char* value; struct TYPE_3__* next; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

char *
property_find(properties list, const char *name)
{
    if (list == NULL || name == NULL || !name[0])
	return (NULL);
    while (list != NULL) {
	if (list->name != NULL && strcmp(list->name, name) == 0)
	    return (list->value);
	list = list->next;
    }
    return (NULL);
}