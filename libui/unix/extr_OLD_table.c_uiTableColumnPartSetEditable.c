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
struct tablePart {int type; int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ g_ptr_array_index (int /*<<< orphan*/ ,int) ; 
#define  partButton 131 
#define  partCheckbox 130 
#define  partImage 129 
#define  partProgressBar 128 

void uiTableColumnPartSetEditable(uiTableColumn *c, int part, int editable)
{
	struct tablePart *p;

	p = (struct tablePart *) g_ptr_array_index(c->parts, part);
	switch (p->type) {
	case partImage:
	case partProgressBar:
		return;
	case partButton:
	case partCheckbox:
		g_object_set(p->r, "sensitive", editable != 0, NULL);
		return;
	}
	g_object_set(p->r, "editable", editable != 0, NULL);
}