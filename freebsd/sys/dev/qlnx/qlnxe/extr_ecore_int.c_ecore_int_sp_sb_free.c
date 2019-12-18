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
struct TYPE_2__ {int /*<<< orphan*/  sb_phys; scalar_t__ sb_virt; } ;
struct ecore_sb_sp_info {TYPE_1__ sb_info; } ;
struct ecore_hwfn {struct ecore_sb_sp_info* p_sp_sb; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_sb_sp_info*) ; 
 struct ecore_sb_sp_info* OSAL_NULL ; 
 int /*<<< orphan*/  SB_ALIGNED_SIZE (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_int_sp_sb_free(struct ecore_hwfn *p_hwfn)
{
	struct ecore_sb_sp_info *p_sb = p_hwfn->p_sp_sb;

	if (!p_sb)
		return;

	if (p_sb->sb_info.sb_virt) {
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_sb->sb_info.sb_virt,
				       p_sb->sb_info.sb_phys,
				       SB_ALIGNED_SIZE(p_hwfn));
	}

	OSAL_FREE(p_hwfn->p_dev, p_sb);
	p_hwfn->p_sp_sb = OSAL_NULL;
}