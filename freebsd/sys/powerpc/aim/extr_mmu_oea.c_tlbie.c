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

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlbie_mtx ; 

__attribute__((used)) static void
tlbie(vm_offset_t va)
{

	mtx_lock_spin(&tlbie_mtx);
	__asm __volatile("ptesync");
	__asm __volatile("tlbie %0" :: "r"(va));
	__asm __volatile("eieio; tlbsync; ptesync");
	mtx_unlock_spin(&tlbie_mtx);
}