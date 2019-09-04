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
struct TYPE_3__ {int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ uiDrawTextLayoutParams ;
struct foreachParams {int /*<<< orphan*/ * attrs; } ;
typedef  int /*<<< orphan*/  PangoAttrList ;

/* Variables and functions */
 int /*<<< orphan*/ * pango_attr_list_new () ; 
 int /*<<< orphan*/  processAttribute ; 
 int /*<<< orphan*/  uiAttributedStringForEachAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct foreachParams*) ; 

PangoAttrList *uiprivAttributedStringToPangoAttrList(uiDrawTextLayoutParams *p)
{
	struct foreachParams fep;

	fep.attrs = pango_attr_list_new();
	uiAttributedStringForEachAttribute(p->String, processAttribute, &fep);
	return fep.attrs;
}