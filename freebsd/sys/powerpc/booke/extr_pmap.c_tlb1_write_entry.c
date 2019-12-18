#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mas2; } ;
typedef  TYPE_1__ tlb_entry_t ;
struct tlbwrite_args {unsigned int idx; TYPE_1__* e; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int _TLB_ENTRY_SHARED ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mfmsr () ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct tlbwrite_args*),int /*<<< orphan*/ ,struct tlbwrite_args*) ; 
 scalar_t__ smp_started ; 
 int /*<<< orphan*/  tlb1_write_entry_int (struct tlbwrite_args*) ; 
 int /*<<< orphan*/  tlb1_write_entry_sync ; 

__attribute__((used)) static void
tlb1_write_entry(tlb_entry_t *e, unsigned int idx)
{
	struct tlbwrite_args args;

	args.e = e;
	args.idx = idx;

#ifdef SMP
	if ((e->mas2 & _TLB_ENTRY_SHARED) && smp_started) {
		mb();
		smp_rendezvous(tlb1_write_entry_sync,
		    tlb1_write_entry_int,
		    tlb1_write_entry_sync, &args);
	} else
#endif
	{
		register_t msr;

		msr = mfmsr();
		__asm __volatile("wrteei 0");
		tlb1_write_entry_int(&args);
		__asm __volatile("wrtee %0" :: "r"(msr));
	}
}