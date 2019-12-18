#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {unsigned int frequency; } ;
struct TYPE_3__ {int nr_pstates; int nominal; } ;

/* Variables and functions */
 int /*<<< orphan*/  idx_to_pstate (int) ; 
 TYPE_2__* powernv_freqs ; 
 TYPE_1__ powernv_pstate_info ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pstate_to_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pstate_id_to_freq(u8 pstate_id)
{
	int i;

	i = pstate_to_idx(pstate_id);
	if (i >= powernv_pstate_info.nr_pstates || i < 0) {
		pr_warn("PState id 0x%x outside of PState table, reporting nominal id 0x%x instead\n",
			pstate_id, idx_to_pstate(powernv_pstate_info.nominal));
		i = powernv_pstate_info.nominal;
	}

	return powernv_freqs[i].frequency;
}