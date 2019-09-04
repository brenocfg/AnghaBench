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
typedef  int /*<<< orphan*/  uiAttributedStringForEachAttributeFunc ;
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */
 int /*<<< orphan*/  uiprivAttrListForEach (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,void*) ; 

void uiAttributedStringForEachAttribute(const uiAttributedString *s, uiAttributedStringForEachAttributeFunc f, void *data)
{
	uiprivAttrListForEach(s->attrs, s, f, data);
}