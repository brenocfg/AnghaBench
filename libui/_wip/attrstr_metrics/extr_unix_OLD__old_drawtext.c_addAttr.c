#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  attrs; int /*<<< orphan*/ * graphemes; } ;
typedef  TYPE_1__ uiDrawTextLayout ;
struct TYPE_7__ {int /*<<< orphan*/  end_index; int /*<<< orphan*/  start_index; } ;
typedef  TYPE_2__ PangoAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  pango_attr_list_insert (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void addAttr(uiDrawTextLayout *layout, PangoAttribute *attr, int startChar, int endChar)
{
	attr->start_index = layout->graphemes[startChar];
	attr->end_index = layout->graphemes[endChar];
	pango_attr_list_insert(layout->attrs, attr);
	// pango_attr_list_insert() takes attr; we don't free it
}