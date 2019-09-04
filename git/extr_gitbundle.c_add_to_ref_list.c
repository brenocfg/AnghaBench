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
struct ref_list {int nr; TYPE_1__* list; int /*<<< orphan*/  alloc; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_to_ref_list(const struct object_id *oid, const char *name,
		struct ref_list *list)
{
	ALLOC_GROW(list->list, list->nr + 1, list->alloc);
	oidcpy(&list->list[list->nr].oid, oid);
	list->list[list->nr].name = xstrdup(name);
	list->nr++;
}