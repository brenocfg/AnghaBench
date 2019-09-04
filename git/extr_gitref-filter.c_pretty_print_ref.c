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
struct ref_format {int dummy; } ;
struct ref_array_item {int /*<<< orphan*/  kind; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_array_item (struct ref_array_item*) ; 
 struct ref_array_item* new_ref_array_item (char const*,struct object_id const*) ; 
 int /*<<< orphan*/  ref_kind_from_refname (char const*) ; 
 int /*<<< orphan*/  show_ref_array_item (struct ref_array_item*,struct ref_format const*) ; 

void pretty_print_ref(const char *name, const struct object_id *oid,
		      const struct ref_format *format)
{
	struct ref_array_item *ref_item;
	ref_item = new_ref_array_item(name, oid);
	ref_item->kind = ref_kind_from_refname(name);
	show_ref_array_item(ref_item, format);
	free_array_item(ref_item);
}