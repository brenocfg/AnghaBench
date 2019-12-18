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
struct foreachParams {int /*<<< orphan*/  attrs; } ;
struct TYPE_4__ {size_t start_index; size_t end_index; } ;
typedef  TYPE_1__ PangoAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  pango_attr_list_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void addattr(struct foreachParams *p, size_t start, size_t end, PangoAttribute *attr)
{
	if (attr == NULL)		// in case of a future attribute
		return;
	attr->start_index = start;
	attr->end_index = end;
	pango_attr_list_insert(p->attrs, attr);
}