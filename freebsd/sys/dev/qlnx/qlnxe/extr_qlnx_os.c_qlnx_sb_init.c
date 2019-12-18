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
typedef  int u16 ;
struct ecore_sb_info {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_main_ptt; } ;
struct ecore_dev {int num_hwfns; struct ecore_hwfn* hwfns; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT2 (int /*<<< orphan*/ *,char*,int,struct ecore_hwfn*,int,int,struct ecore_sb_info*,void*,void*) ; 
 int ecore_int_sb_init (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_sb_info*,void*,scalar_t__,int) ; 

__attribute__((used)) static int
qlnx_sb_init(struct ecore_dev *cdev, struct ecore_sb_info *sb_info,
	void *sb_virt_addr, bus_addr_t sb_phy_addr, u16 sb_id)
{
        struct ecore_hwfn	*p_hwfn;
        int			hwfn_index, rc;
        u16			rel_sb_id;

        hwfn_index = sb_id % cdev->num_hwfns;
        p_hwfn = &cdev->hwfns[hwfn_index];
        rel_sb_id = sb_id / cdev->num_hwfns;

        QL_DPRINT2(((qlnx_host_t *)cdev), 
                "hwfn_index = %d p_hwfn = %p sb_id = 0x%x rel_sb_id = 0x%x \
                sb_info = %p sb_virt_addr = %p sb_phy_addr = %p\n",
                hwfn_index, p_hwfn, sb_id, rel_sb_id, sb_info,
                sb_virt_addr, (void *)sb_phy_addr);

        rc = ecore_int_sb_init(p_hwfn, p_hwfn->p_main_ptt, sb_info,
                             sb_virt_addr, sb_phy_addr, rel_sb_id);

        return rc;
}