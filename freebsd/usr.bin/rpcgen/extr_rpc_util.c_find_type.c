#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bas_type ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* typ_list_h ; 

bas_type *
find_type(const char *type)
{
	bas_type * ptr;

	ptr = typ_list_h;
	while (ptr != NULL)
	{
		if (strcmp(ptr->name, type) == 0)
			return (ptr);
		else
			ptr = ptr->next;
	}
	return (NULL);
}