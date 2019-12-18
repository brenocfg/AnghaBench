#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ecore_ll2_info {int my_id; TYPE_2__ tx_queue; TYPE_1__ rx_queue; int /*<<< orphan*/  mutex; } ;
struct ecore_hwfn {struct ecore_ll2_info* p_ll2_info; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_MAX_NUM_OF_LL2_CONNECTIONS ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OSAL_MUTEX_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 scalar_t__ OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 struct ecore_ll2_info* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_ll2_free (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_ll2_alloc(struct ecore_hwfn *p_hwfn)
{
	struct ecore_ll2_info *p_ll2_info;
	u8 i;

	/* Allocate LL2's set struct */
	p_ll2_info = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
				 sizeof(struct ecore_ll2_info) *
				 ECORE_MAX_NUM_OF_LL2_CONNECTIONS);
	if (!p_ll2_info) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `struct ecore_ll2'\n");
		return ECORE_NOMEM;
	}

	p_hwfn->p_ll2_info = p_ll2_info;

	for (i = 0; i < ECORE_MAX_NUM_OF_LL2_CONNECTIONS; i++) {
#ifdef CONFIG_ECORE_LOCK_ALLOC
		if (OSAL_MUTEX_ALLOC(p_hwfn, &p_ll2_info[i].mutex))
			goto handle_err;
		if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_ll2_info[i].rx_queue.lock))
			goto handle_err;
		if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_ll2_info[i].tx_queue.lock))
			goto handle_err;
#endif
		p_ll2_info[i].my_id = i;
	}

	return ECORE_SUCCESS;
#ifdef CONFIG_ECORE_LOCK_ALLOC
handle_err:
	ecore_ll2_free(p_hwfn);
	return ECORE_NOMEM;
#endif
}