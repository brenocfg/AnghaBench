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
struct mt_status_entry {scalar_t__ var_type; char* entry_name; char* value; char* desc; int /*<<< orphan*/ * parent; } ;
struct mt_print_params {int flags; } ;

/* Variables and functions */
 int MT_PF_FULL_PATH ; 
 int MT_PF_VERBOSE ; 
 scalar_t__ MT_TYPE_NODE ; 
 int /*<<< orphan*/  mt_param_parent_print (int /*<<< orphan*/ *,struct mt_print_params*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 

void
mt_param_entry_print(struct mt_status_entry *entry, void *arg)
{
	struct mt_print_params *print_params;

	print_params = (struct mt_print_params *)arg;

	/*
	 * We don't want to print nodes.
	 */
	if (entry->var_type == MT_TYPE_NODE)
		return;

	if ((print_params->flags & MT_PF_FULL_PATH)
	 && (entry->parent != NULL))
		mt_param_parent_print(entry->parent, print_params);

	printf("%s: %s", entry->entry_name, entry->value);
	if ((print_params->flags & MT_PF_VERBOSE)
	 && (entry->desc != NULL)
	 && (strlen(entry->desc) > 0))
		printf(" (%s)", entry->desc);
	printf("\n");
}