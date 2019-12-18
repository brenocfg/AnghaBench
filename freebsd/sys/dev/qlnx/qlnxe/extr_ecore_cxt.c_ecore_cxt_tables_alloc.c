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
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_SUCCESS ; 
 int ecore_cid_map_alloc (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_cxt_mngr_free (struct ecore_hwfn*) ; 
 int ecore_cxt_src_t2_alloc (struct ecore_hwfn*) ; 
 int ecore_ilt_shadow_alloc (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_cxt_tables_alloc(struct ecore_hwfn *p_hwfn)
{
	enum _ecore_status_t    rc;

	/* Allocate the ILT shadow table */
	rc = ecore_ilt_shadow_alloc(p_hwfn);
	if (rc) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate ilt memory\n");
		goto tables_alloc_fail;
	}

	/* Allocate the T2  table */
	rc = ecore_cxt_src_t2_alloc(p_hwfn);
	if (rc) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate T2 memory\n");
		goto tables_alloc_fail;
	}

	/* Allocate and initialize the acquired cids bitmaps */
	rc = ecore_cid_map_alloc(p_hwfn);
	if (rc) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate cid maps\n");
		goto tables_alloc_fail;
	}

	return ECORE_SUCCESS;

tables_alloc_fail:
	ecore_cxt_mngr_free(p_hwfn);
	return rc;
}