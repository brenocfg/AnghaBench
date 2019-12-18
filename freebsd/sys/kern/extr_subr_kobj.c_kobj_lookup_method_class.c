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
typedef  scalar_t__ kobjop_desc_t ;
struct TYPE_5__ {scalar_t__ desc; } ;
typedef  TYPE_1__ kobj_method_t ;
typedef  TYPE_2__* kobj_class_t ;
struct TYPE_6__ {TYPE_1__* methods; } ;

/* Variables and functions */

__attribute__((used)) static kobj_method_t*
kobj_lookup_method_class(kobj_class_t cls, kobjop_desc_t desc)
{
	kobj_method_t *methods = cls->methods;
	kobj_method_t *ce;

	for (ce = methods; ce && ce->desc; ce++) {
		if (ce->desc == desc) {
			return ce;
		}
	}

	return NULL;
}