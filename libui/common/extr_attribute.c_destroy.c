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
struct TYPE_5__ {int /*<<< orphan*/  features; TYPE_2__* family; } ;
struct TYPE_6__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ uiAttribute ;

/* Variables and functions */
#define  uiAttributeTypeFamily 129 
#define  uiAttributeTypeFeatures 128 
 int /*<<< orphan*/  uiFreeOpenTypeFeatures (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivFree (TYPE_2__*) ; 

__attribute__((used)) static void destroy(uiAttribute *a)
{
	switch (a->type) {
	case uiAttributeTypeFamily:
		uiprivFree(a->u.family);
		break;
	case uiAttributeTypeFeatures:
		uiFreeOpenTypeFeatures(a->u.features);
		break;
	}
	uiprivFree(a);
}