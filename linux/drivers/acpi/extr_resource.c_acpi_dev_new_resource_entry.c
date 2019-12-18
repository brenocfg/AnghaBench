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
struct resource_win {int /*<<< orphan*/  offset; int /*<<< orphan*/  res; } ;
struct resource_entry {int /*<<< orphan*/  offset; int /*<<< orphan*/ * res; } ;
struct res_proc_context {int /*<<< orphan*/  count; int /*<<< orphan*/  list; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  resource_list_add_tail (struct resource_entry*,int /*<<< orphan*/ ) ; 
 struct resource_entry* resource_list_create_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status acpi_dev_new_resource_entry(struct resource_win *win,
					       struct res_proc_context *c)
{
	struct resource_entry *rentry;

	rentry = resource_list_create_entry(NULL, 0);
	if (!rentry) {
		c->error = -ENOMEM;
		return AE_NO_MEMORY;
	}
	*rentry->res = win->res;
	rentry->offset = win->offset;
	resource_list_add_tail(rentry, c->list);
	c->count++;
	return AE_OK;
}