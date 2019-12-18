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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ecore_dev {int dummy; } ;
typedef  int /*<<< orphan*/  osal_size_t ;
typedef  enum ecore_chain_cnt_type { ____Placeholder_ecore_chain_cnt_type } ecore_chain_cnt_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,unsigned long long) ; 
 int ECORE_CHAIN_CNT_TYPE_U16 ; 
 int ECORE_CHAIN_CNT_TYPE_U32 ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_U16_MAX ; 
 scalar_t__ ECORE_U32_MAX ; 
 scalar_t__ ELEMS_PER_PAGE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_chain_alloc_sanity_check(struct ecore_dev *p_dev,
			       enum ecore_chain_cnt_type cnt_type,
			       osal_size_t elem_size, u32 page_cnt)
{
	u64 chain_size = ELEMS_PER_PAGE(elem_size) * page_cnt;

	/* The actual chain size can be larger than the maximal possible value
	 * after rounding up the requested elements number to pages, and after
	 * taking into acount the unusuable elements (next-ptr elements).
	 * The size of a "u16" chain can be (U16_MAX + 1) since the chain
	 * size/capacity fields are of a u32 type.
	 */
	if ((cnt_type == ECORE_CHAIN_CNT_TYPE_U16 &&
	     chain_size > ((u32)ECORE_U16_MAX + 1)) ||
	    (cnt_type == ECORE_CHAIN_CNT_TYPE_U32 &&
	     chain_size > ECORE_U32_MAX)) {
		DP_NOTICE(p_dev, true,
			  "The actual chain size (0x%llx) is larger than the maximal possible value\n",
			  (unsigned long long)chain_size);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}