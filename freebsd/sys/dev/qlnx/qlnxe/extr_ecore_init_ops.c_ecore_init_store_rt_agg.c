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
typedef  int u32 ;
struct TYPE_2__ {int* init_val; int* b_valid; } ;
struct ecore_hwfn {TYPE_1__ rt_data; } ;
typedef  int osal_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int,int,int) ; 
 int RUNTIME_ARRAY_SIZE ; 

void ecore_init_store_rt_agg(struct ecore_hwfn *p_hwfn,
			     u32 rt_offset, u32 *p_val,
			     osal_size_t size)
{
	osal_size_t i;

	if ((rt_offset + size - 1) >= RUNTIME_ARRAY_SIZE) {
		DP_ERR(p_hwfn,
		       "Avoid storing values in rt_data at indices %u-%u since RUNTIME_ARRAY_SIZE is %u!\n",
		       rt_offset, (u32)(rt_offset + size - 1),
		       RUNTIME_ARRAY_SIZE);
		return;
	}

	for (i = 0; i < size / sizeof(u32); i++) {
		p_hwfn->rt_data.init_val[rt_offset + i] = p_val[i];
		p_hwfn->rt_data.b_valid[rt_offset + i] = true;

	}
}