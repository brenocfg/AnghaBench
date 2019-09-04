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
struct TYPE_4__ {scalar_t__ refcount; scalar_t__ ownedByUser; } ;
typedef  TYPE_1__ uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  destroy (TYPE_1__*) ; 

void uiprivAttributeRelease(uiAttribute *a)
{
	if (a->ownedByUser)
		/* TODO implementation bug: we can't release an attribute we don't own */;
	a->refcount--;
	if (a->refcount == 0)
		destroy(a);
}