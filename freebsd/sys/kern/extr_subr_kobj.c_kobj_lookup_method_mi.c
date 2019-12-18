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
typedef  int /*<<< orphan*/  kobjop_desc_t ;
typedef  int /*<<< orphan*/  kobj_method_t ;
typedef  TYPE_1__* kobj_class_t ;
struct TYPE_4__ {struct TYPE_4__** baseclasses; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kobj_lookup_method_class (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kobj_method_t*
kobj_lookup_method_mi(kobj_class_t cls,
		      kobjop_desc_t desc)
{
	kobj_method_t *ce;
	kobj_class_t *basep;

	ce = kobj_lookup_method_class(cls, desc);
	if (ce)
		return ce;

	basep = cls->baseclasses;
	if (basep) {
		for (; *basep; basep++) {
			ce = kobj_lookup_method_mi(*basep, desc);
			if (ce)
				return ce;
		}
	}

	return NULL;
}