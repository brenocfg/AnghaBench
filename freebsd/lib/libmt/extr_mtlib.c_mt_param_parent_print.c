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
struct mt_status_entry {char* entry_name; struct mt_status_entry* parent; } ;
struct mt_print_params {int flags; int /*<<< orphan*/  root_name; } ;

/* Variables and functions */
 int MT_PF_INCLUDE_ROOT ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
mt_param_parent_print(struct mt_status_entry *entry,
    struct mt_print_params *print_params)
{
	if (entry->parent != NULL)
		mt_param_parent_print(entry->parent, print_params);

	if (((print_params->flags & MT_PF_INCLUDE_ROOT) == 0)
	 && (strcmp(entry->entry_name, print_params->root_name) == 0))
		return;

	printf("%s.", entry->entry_name);
}