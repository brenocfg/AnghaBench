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
struct TYPE_3__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ uiAttributedString ;
typedef  int /*<<< orphan*/  uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  uiprivAttrListInsertAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 

void uiAttributedStringSetAttribute(uiAttributedString *s, uiAttribute *a, size_t start, size_t end)
{
	uiprivAttrListInsertAttribute(s->attrs, a, start, end);
}