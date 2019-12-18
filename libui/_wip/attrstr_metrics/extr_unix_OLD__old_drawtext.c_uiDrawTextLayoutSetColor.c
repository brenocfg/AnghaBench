#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  scalar_t__ guint16 ;
typedef  int /*<<< orphan*/  PangoAttribute ;

/* Variables and functions */
 int /*<<< orphan*/ * FUTURE_pango_attr_foreground_alpha_new (scalar_t__) ; 
 int /*<<< orphan*/  addAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * pango_attr_foreground_new (scalar_t__,scalar_t__,scalar_t__) ; 

void uiDrawTextLayoutSetColor(uiDrawTextLayout *layout, int startChar, int endChar, double r, double g, double b, double a)
{
	PangoAttribute *attr;
	guint16 rr, gg, bb, aa;

	rr = (guint16) (r * 65535);
	gg = (guint16) (g * 65535);
	bb = (guint16) (b * 65535);
	aa = (guint16) (a * 65535);

	attr = pango_attr_foreground_new(rr, gg, bb);
	addAttr(layout, attr, startChar, endChar);

	// TODO what if aa == 0?
	attr = FUTURE_pango_attr_foreground_alpha_new(aa);
	if (attr != NULL)
		addAttr(layout, attr, startChar, endChar);
}