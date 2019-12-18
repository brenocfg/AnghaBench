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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  scalar_t__ vm_object_t ;
typedef  int /*<<< orphan*/  objtype_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  _vm_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  obj_zone ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_object_t
vm_object_allocate(objtype_t type, vm_pindex_t size)
{
	vm_object_t object;

	object = (vm_object_t)uma_zalloc(obj_zone, M_WAITOK);
	_vm_object_allocate(type, size, object);
	return (object);
}