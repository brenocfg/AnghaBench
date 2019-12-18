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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 uintptr_t VM_MAXUSER_ADDRESS ; 
 scalar_t__ cp_slow0 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ fast_copyout ; 
 int /*<<< orphan*/  pmap_get_kcr3 () ; 
 scalar_t__ suword16_fast_tramp (void volatile*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suword16_slow0 ; 

int
suword16(volatile void *base, int word)
{

	if ((uintptr_t)base + sizeof(uint16_t) < (uintptr_t)base ||
	    (uintptr_t)base + sizeof(uint16_t) > VM_MAXUSER_ADDRESS)
		return (-1);
	if (fast_copyout && suword16_fast_tramp(base, word, pmap_get_kcr3())
	    == 0)
		return (0);
	return (cp_slow0((vm_offset_t)base, sizeof(int16_t), true,
	    suword16_slow0, &word) != 0 ? -1 : 0);
}