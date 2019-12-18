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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_extract_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_paddr_t
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	vm_paddr_t pa;

	PMAP_LOCK(pmap);
	pa = pmap_extract_locked(pmap, va);
	PMAP_UNLOCK(pmap);
	return (pa);
}