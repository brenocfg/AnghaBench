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
typedef  int /*<<< orphan*/  guint16 ;
typedef  int /*<<< orphan*/  PangoAttribute ;

/* Variables and functions */
 int /*<<< orphan*/ * newFGAlphaAttr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

PangoAttribute *uiprivFUTURE_pango_attr_foreground_alpha_new(guint16 alpha)
{
	if (newFGAlphaAttr == NULL)
		return NULL;
	return (*newFGAlphaAttr)(alpha);
}