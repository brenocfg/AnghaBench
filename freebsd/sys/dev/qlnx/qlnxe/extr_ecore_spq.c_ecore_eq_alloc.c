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
typedef  union event_ring_element {int dummy; } event_ring_element ;
typedef  int /*<<< orphan*/  u16 ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct ecore_eq* p_eq; } ;
struct ecore_eq {int /*<<< orphan*/  p_fw_cons; int /*<<< orphan*/  eq_sb_index; int /*<<< orphan*/  chain; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  ECORE_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_PRODUCE ; 
 int ECORE_NOMEM ; 
 scalar_t__ ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_eq*) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 struct ecore_eq* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_eq_completion ; 
 int /*<<< orphan*/  ecore_int_register_cb (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_eq*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_eq_alloc(struct ecore_hwfn *p_hwfn, u16 num_elem)
{
	struct ecore_eq	*p_eq;

	/* Allocate EQ struct */
	p_eq = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_eq));
	if (!p_eq) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `struct ecore_eq'\n");
		return ECORE_NOMEM;
	}

	/* Allocate and initialize EQ chain*/
	if (ecore_chain_alloc(p_hwfn->p_dev,
			      ECORE_CHAIN_USE_TO_PRODUCE,
			      ECORE_CHAIN_MODE_PBL,
			      ECORE_CHAIN_CNT_TYPE_U16,
			      num_elem,
			      sizeof(union event_ring_element),
			      &p_eq->chain, OSAL_NULL) != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate eq chain\n");
		goto eq_allocate_fail;
	}

	/* register EQ completion on the SP SB */
	ecore_int_register_cb(p_hwfn, ecore_eq_completion,
			      p_eq, &p_eq->eq_sb_index, &p_eq->p_fw_cons);

	p_hwfn->p_eq = p_eq;
	return ECORE_SUCCESS;

eq_allocate_fail:
	OSAL_FREE(p_hwfn->p_dev, p_eq);
	return ECORE_NOMEM;
}