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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  PangoAttribute ;

/* Variables and functions */
 int /*<<< orphan*/ * newFeaturesAttr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/  const*) ; 

PangoAttribute *uiprivFUTURE_pango_attr_font_features_new(const gchar *features)
{
	if (newFeaturesAttr == NULL)
		return NULL;
	return (*newFeaturesAttr)(features);
}