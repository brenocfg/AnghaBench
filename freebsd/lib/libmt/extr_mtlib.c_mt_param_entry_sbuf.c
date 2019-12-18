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
struct sbuf {int dummy; } ;
struct mt_status_entry {scalar_t__ var_type; int /*<<< orphan*/ * desc; int /*<<< orphan*/  value; int /*<<< orphan*/  entry_name; int /*<<< orphan*/ * parent; } ;
struct mt_print_params {int flags; } ;

/* Variables and functions */
 int MT_PF_FULL_PATH ; 
 int MT_PF_VERBOSE ; 
 scalar_t__ MT_TYPE_NODE ; 
 int /*<<< orphan*/  mt_param_parent_sbuf (struct sbuf*,int /*<<< orphan*/ *,struct mt_print_params*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

void
mt_param_entry_sbuf(struct sbuf *sb, struct mt_status_entry *entry, void *arg)
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
		mt_param_parent_sbuf(sb, entry->parent, print_params);

	sbuf_printf(sb, "%s: %s", entry->entry_name, entry->value);
	if ((print_params->flags & MT_PF_VERBOSE)
	 && (entry->desc != NULL)
	 && (strlen(entry->desc) > 0))
		sbuf_printf(sb, " (%s)", entry->desc);
	sbuf_printf(sb, "\n");

}