#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {uintptr_t* tlb_lock; int /*<<< orphan*/  tid_next; } ;
struct pcpu {TYPE_1__ pc_booke; } ;

/* Variables and functions */
 int RES_GRANULE ; 
 int /*<<< orphan*/  TID_MIN ; 
 uintptr_t TLB_UNLOCKED ; 
 uintptr_t* tlb0_miss_locks ; 

void
cpu_pcpu_init(struct pcpu *pcpu, int cpuid, size_t sz)
{

	pcpu->pc_booke.tid_next = TID_MIN;

#ifdef SMP
	uintptr_t *ptr;
	int words_per_gran = RES_GRANULE / sizeof(uintptr_t);

	ptr = &tlb0_miss_locks[cpuid * words_per_gran];
	pcpu->pc_booke.tlb_lock = ptr;
	*ptr = TLB_UNLOCKED;
	*(ptr + 1) = 0;		/* recurse counter */
#endif
}