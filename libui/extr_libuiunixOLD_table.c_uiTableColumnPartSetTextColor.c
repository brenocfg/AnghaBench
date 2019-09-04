#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parts; } ;
typedef  TYPE_1__ uiTableColumn ;
struct tablePart {int colorColumn; } ;

/* Variables and functions */
 scalar_t__ g_ptr_array_index (int /*<<< orphan*/ ,int) ; 

void uiTableColumnPartSetTextColor(uiTableColumn *c, int part, int modelColumn)
{
	struct tablePart *p;

	p = (struct tablePart *) g_ptr_array_index(c->parts, part);
	p->colorColumn = modelColumn;
	// TODO refresh table
}