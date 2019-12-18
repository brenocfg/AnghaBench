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
typedef  int u32 ;
struct ecore_ooo_info {int cid_base; int max_num_archipelagos; struct ecore_ooo_archipelago* p_archipelagos_mem; } ;
struct ecore_ooo_archipelago {int /*<<< orphan*/  isles_list; } ;

/* Variables and functions */
 scalar_t__ OSAL_LIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 struct ecore_ooo_archipelago* OSAL_NULL ; 

__attribute__((used)) static struct ecore_ooo_archipelago *
ecore_ooo_seek_archipelago(struct ecore_ooo_info *p_ooo_info, u32 cid)
{
	u32 idx = (cid & 0xffff) - p_ooo_info->cid_base;
	struct ecore_ooo_archipelago *p_archipelago;

	if (idx >= p_ooo_info->max_num_archipelagos)
		return OSAL_NULL;

	p_archipelago = &p_ooo_info->p_archipelagos_mem[idx];

	if (OSAL_LIST_IS_EMPTY(&p_archipelago->isles_list))
		return OSAL_NULL;

	return p_archipelago;
}