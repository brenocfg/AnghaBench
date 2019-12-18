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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  scalar_t__ osal_uintptr_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,char const*,unsigned long long,void*,unsigned long long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 void* OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int OSAL_PAGE_SIZE ; 
 int ecore_dmae_host2host (struct ecore_hwfn*,struct ecore_ptt*,int,int,int,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_dmae_sanity(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       const char *phase)
{
	u32 size = OSAL_PAGE_SIZE / 2, val;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	dma_addr_t p_phys;
	void *p_virt;
	u32 *p_tmp;

	p_virt = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, &p_phys, 2 * size);
	if (!p_virt) {
		DP_NOTICE(p_hwfn, false,
			  "DMAE sanity [%s]: failed to allocate memory\n",
			  phase);
		return ECORE_NOMEM;
	}

	/* Fill the bottom half of the allocated memory with a known pattern */
	for (p_tmp = (u32 *)p_virt;
	     p_tmp < (u32 *)((u8 *)p_virt + size);
	     p_tmp++) {
		/* Save the address itself as the value */
		val = (u32)(osal_uintptr_t)p_tmp;
		*p_tmp = val;
	}

	/* Zero the top half of the allocated memory */
	OSAL_MEM_ZERO((u8 *)p_virt + size, size);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "DMAE sanity [%s]: src_addr={phys 0x%llx, virt %p}, dst_addr={phys 0x%llx, virt %p}, size 0x%x\n",
		   phase, (unsigned long long)p_phys, p_virt,
		   (unsigned long long)(p_phys + size), (u8 *)p_virt + size,
		   size);

	rc = ecore_dmae_host2host(p_hwfn, p_ptt, p_phys, p_phys + size,
				  size / 4 /* size_in_dwords */,
				  OSAL_NULL /* default parameters */);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false,
			  "DMAE sanity [%s]: ecore_dmae_host2host() failed. rc = %d.\n",
			  phase, rc);
		goto out;
	}

	/* Verify that the top half of the allocated memory has the pattern */
	for (p_tmp = (u32 *)((u8 *)p_virt + size);
	     p_tmp < (u32 *)((u8 *)p_virt + (2 * size));
	     p_tmp++) {
		/* The corresponding address in the bottom half */
		val = (u32)(osal_uintptr_t)p_tmp - size;

		if (*p_tmp != val) {
			DP_NOTICE(p_hwfn, false,
				  "DMAE sanity [%s]: addr={phys 0x%llx, virt %p}, read_val 0x%08x, expected_val 0x%08x\n",
				  phase,
				  (unsigned long long)(p_phys + (u32)((u8 *)p_tmp - (u8 *)p_virt)),
				  p_tmp, *p_tmp, val);
			rc = ECORE_UNKNOWN_ERROR;
			goto out;
		}
	}

out:
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev, p_virt, p_phys, 2 * size);
	return rc;
}