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
struct TYPE_3__ {int /*<<< orphan*/  attrs; int /*<<< orphan*/  defaultFont; } ;
typedef  TYPE_1__ uiDrawTextLayout ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  pango_font_describe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepareLayout(uiDrawTextLayout *layout, PangoLayout *pl)
{
	// again, this makes a copy
	desc = pango_font_describe(layout->defaultFont);

	pango_layout_set_attributes(pl, layout->attrs);
}