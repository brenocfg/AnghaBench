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
struct tte {int /*<<< orphan*/  tte_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct tte*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  TTE_ZERO (struct tte*) ; 
 struct tte* tsb_kvtotte (int /*<<< orphan*/ ) ; 

void
pmap_kremove_flags(vm_offset_t va)
{
	struct tte *tp;

	tp = tsb_kvtotte(va);
	CTR3(KTR_PMAP, "pmap_kremove_flags: va=%#lx tp=%p data=%#lx", va, tp,
	    tp->tte_data);
	TTE_ZERO(tp);
}