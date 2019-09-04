#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiOpenTypeFeatures ;
struct TYPE_5__ {int /*<<< orphan*/  features; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ uiAttribute ;

/* Variables and functions */
 TYPE_2__* newAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAttributeTypeFeatures ; 
 int /*<<< orphan*/  uiOpenTypeFeaturesClone (int /*<<< orphan*/  const*) ; 

uiAttribute *uiNewFeaturesAttribute(const uiOpenTypeFeatures *otf)
{
	uiAttribute *a;

	a = newAttribute(uiAttributeTypeFeatures);
	a->u.features = uiOpenTypeFeaturesClone(otf);
	return a;
}