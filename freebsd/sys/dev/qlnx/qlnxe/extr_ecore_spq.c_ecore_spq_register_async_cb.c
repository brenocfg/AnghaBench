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
struct ecore_hwfn {TYPE_1__* p_spq; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  ecore_spq_async_comp_cb ;
struct TYPE_2__ {int /*<<< orphan*/ * async_comp_cb; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int MAX_PROTOCOL_TYPE ; 

enum _ecore_status_t
ecore_spq_register_async_cb(struct ecore_hwfn *p_hwfn,
			    enum protocol_type protocol_id,
			    ecore_spq_async_comp_cb cb)
{
	if (!p_hwfn->p_spq || (protocol_id >= MAX_PROTOCOL_TYPE)) {
		return ECORE_INVAL;
	}

	p_hwfn->p_spq->async_comp_cb[protocol_id] = cb;
	return ECORE_SUCCESS;
}