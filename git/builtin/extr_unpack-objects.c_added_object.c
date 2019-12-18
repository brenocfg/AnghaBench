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
struct delta_info {scalar_t__ base_offset; struct delta_info* next; int /*<<< orphan*/  size; int /*<<< orphan*/  delta; int /*<<< orphan*/  nr; int /*<<< orphan*/  base_oid; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 struct delta_info* delta_list ; 
 int /*<<< orphan*/  free (struct delta_info*) ; 
 TYPE_1__* obj_list ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_delta (int /*<<< orphan*/ ,int,void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void added_object(unsigned nr, enum object_type type,
			 void *data, unsigned long size)
{
	struct delta_info **p = &delta_list;
	struct delta_info *info;

	while ((info = *p) != NULL) {
		if (oideq(&info->base_oid, &obj_list[nr].oid) ||
		    info->base_offset == obj_list[nr].offset) {
			*p = info->next;
			p = &delta_list;
			resolve_delta(info->nr, type, data, size,
				      info->delta, info->size);
			free(info);
			continue;
		}
		p = &info->next;
	}
}