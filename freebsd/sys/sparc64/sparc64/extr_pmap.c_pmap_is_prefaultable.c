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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsb_tte_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
pmap_is_prefaultable(pmap_t pmap, vm_offset_t addr)
{
	boolean_t rv;

	PMAP_LOCK(pmap);
	rv = tsb_tte_lookup(pmap, addr) == NULL;
	PMAP_UNLOCK(pmap);
	return (rv);
}