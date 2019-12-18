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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_VM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  _vm_map_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapzone ; 
 int /*<<< orphan*/  uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_map_t
vm_map_create(pmap_t pmap, vm_offset_t min, vm_offset_t max)
{
	vm_map_t result;

	result = uma_zalloc(mapzone, M_WAITOK);
	CTR1(KTR_VM, "vm_map_create: %p", result);
	_vm_map_init(result, pmap, min, max);
	return (result);
}