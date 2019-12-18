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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* p_virt; } ;
struct ecore_vf_info {TYPE_2__ bulletin; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_3__ {int valid_bitmap; int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int MAC_ADDR_FORCED ; 
 int /*<<< orphan*/ * OSAL_NULL ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

u8 *ecore_iov_bulletin_get_forced_mac(struct ecore_hwfn *p_hwfn,
				      u16 rel_vf_id)
{
	struct ecore_vf_info *p_vf;

	p_vf = ecore_iov_get_vf_info(p_hwfn, rel_vf_id, true);
	if (!p_vf || !p_vf->bulletin.p_virt)
		return OSAL_NULL;

	if (!(p_vf->bulletin.p_virt->valid_bitmap & (1 << MAC_ADDR_FORCED)))
		return OSAL_NULL;

	return p_vf->bulletin.p_virt->mac;
}