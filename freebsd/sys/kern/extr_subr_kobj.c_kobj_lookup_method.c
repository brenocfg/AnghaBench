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
typedef  TYPE_1__* kobjop_desc_t ;
typedef  int /*<<< orphan*/  kobj_method_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
struct TYPE_4__ {int /*<<< orphan*/  deflt; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kobj_lookup_method_mi (int /*<<< orphan*/ ,TYPE_1__*) ; 

kobj_method_t*
kobj_lookup_method(kobj_class_t cls,
		   kobj_method_t **cep,
		   kobjop_desc_t desc)
{
	kobj_method_t *ce;

	ce = kobj_lookup_method_mi(cls, desc);
	if (!ce)
		ce = &desc->deflt;
	if (cep)
		*cep = ce;
	return ce;
}