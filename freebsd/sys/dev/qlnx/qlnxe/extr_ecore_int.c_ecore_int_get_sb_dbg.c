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
struct ecore_sb_info_dbg {int* pi; void* igu_cons; void* igu_prod; } ;
struct ecore_sb_info {int igu_sb_id; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CAU_REG_PI_MEMORY ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IGU_REG_CONSUMER_MEM ; 
 scalar_t__ IGU_REG_PRODUCER_MEMORY ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int NUM_OF_SBS (int /*<<< orphan*/ ) ; 
 int PIS_PER_SB_E4 ; 
 void* ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__) ; 

enum _ecore_status_t ecore_int_get_sb_dbg(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt,
					  struct ecore_sb_info *p_sb,
					  struct ecore_sb_info_dbg *p_info)
{
	u16 sbid = p_sb->igu_sb_id;
	int i;

	if (IS_VF(p_hwfn->p_dev))
		return ECORE_INVAL;

	if (sbid > NUM_OF_SBS(p_hwfn->p_dev))
		return ECORE_INVAL;

	p_info->igu_prod = ecore_rd(p_hwfn, p_ptt,
				    IGU_REG_PRODUCER_MEMORY + sbid * 4);
	p_info->igu_cons = ecore_rd(p_hwfn, p_ptt,
				    IGU_REG_CONSUMER_MEM + sbid * 4);

	for (i = 0; i < PIS_PER_SB_E4; i++)
		p_info->pi[i] = (u16)ecore_rd(p_hwfn, p_ptt,
					      CAU_REG_PI_MEMORY +
					      sbid * 4 * PIS_PER_SB_E4 + i * 4);

	return ECORE_SUCCESS;
}