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
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
struct ecore_bmap {int max_count; int /*<<< orphan*/  name; int /*<<< orphan*/  bitmap; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QEDR_MAX_BMAP_NAME ; 

enum _ecore_status_t ecore_rdma_bmap_alloc(struct ecore_hwfn *p_hwfn,
					   struct ecore_bmap *bmap,
					   u32		    max_count,
					   char              *name)
{
	u32 size_in_bytes;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "max_count = %08x\n", max_count);

	bmap->max_count = max_count;

	if (!max_count) {
		bmap->bitmap = OSAL_NULL;
		return ECORE_SUCCESS;
	}

	size_in_bytes = sizeof(unsigned long) *
		DIV_ROUND_UP(max_count, (sizeof(unsigned long) * 8));

	bmap->bitmap = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, size_in_bytes);
	if (!bmap->bitmap)
	{
		DP_NOTICE(p_hwfn, false,
			  "ecore bmap alloc failed: cannot allocate memory (bitmap). rc = %d\n",
			  ECORE_NOMEM);
		return ECORE_NOMEM;
	}

	OSAL_SNPRINTF(bmap->name, QEDR_MAX_BMAP_NAME, "%s", name);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ECORE_SUCCESS\n");
	return ECORE_SUCCESS;
}