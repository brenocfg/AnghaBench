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
typedef  int uint32_t ;
struct tlbwrite_args {int idx; TYPE_1__* e; } ;
struct TYPE_2__ {int mas1; int mas2; int mas3; int mas7; } ;

/* Variables and functions */
#define  FSL_E500mc 131 
#define  FSL_E500v2 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 int MAS0_ESEL (int) ; 
 int MAS0_TLBSEL (int) ; 
 int /*<<< orphan*/  SPR_MAS0 ; 
 int /*<<< orphan*/  SPR_MAS1 ; 
 int /*<<< orphan*/  SPR_MAS2 ; 
 int /*<<< orphan*/  SPR_MAS3 ; 
 int /*<<< orphan*/  SPR_MAS7 ; 
 int /*<<< orphan*/  SPR_MAS8 ; 
 int mfpvr () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int tlb1_find_free () ; 

__attribute__((used)) static void
tlb1_write_entry_int(void *arg)
{
	struct tlbwrite_args *args = arg;
	uint32_t idx, mas0;

	idx = args->idx;
	if (idx == -1) {
		idx = tlb1_find_free();
		if (idx == -1)
			panic("No free TLB1 entries!\n");
	}
	/* Select entry */
	mas0 = MAS0_TLBSEL(1) | MAS0_ESEL(idx);

	mtspr(SPR_MAS0, mas0);
	mtspr(SPR_MAS1, args->e->mas1);
	mtspr(SPR_MAS2, args->e->mas2);
	mtspr(SPR_MAS3, args->e->mas3);
	switch ((mfpvr() >> 16) & 0xFFFF) {
	case FSL_E500mc:
	case FSL_E5500:
	case FSL_E6500:
		mtspr(SPR_MAS8, 0);
		/* FALLTHROUGH */
	case FSL_E500v2:
		mtspr(SPR_MAS7, args->e->mas7);
		break;
	default:
		break;
	}

	__asm __volatile("isync; tlbwe; isync; msync");

}