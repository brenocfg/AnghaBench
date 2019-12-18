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
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  ecore_iwarp_free_prealloc_ep (struct ecore_hwfn*) ; 
 int ecore_iwarp_ll2_stop (struct ecore_hwfn*) ; 
 int ecore_iwarp_wait_for_all_cids (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_spq_unregister_async_cb (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t
ecore_iwarp_stop(struct ecore_hwfn *p_hwfn)
{
	enum _ecore_status_t rc;

	ecore_iwarp_free_prealloc_ep(p_hwfn);
	rc = ecore_iwarp_wait_for_all_cids(p_hwfn);
	if (rc != ECORE_SUCCESS)
		return rc;

	ecore_spq_unregister_async_cb(p_hwfn, PROTOCOLID_IWARP);

	return ecore_iwarp_ll2_stop(p_hwfn);
}