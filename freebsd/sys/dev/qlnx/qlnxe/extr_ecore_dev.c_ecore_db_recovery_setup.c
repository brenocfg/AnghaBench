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
struct TYPE_3__ {scalar_t__ db_recovery_counter; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct ecore_hwfn {TYPE_1__ db_recovery_info; TYPE_2__* p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_SPQ ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_LIST_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t ecore_db_recovery_setup(struct ecore_hwfn *p_hwfn)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_SPQ, "Setting up db recovery\n");

	/* make sure db_size was set in p_dev */
	if (!p_hwfn->p_dev->db_size) {
		DP_ERR(p_hwfn->p_dev, "db_size not set\n");
		return ECORE_INVAL;
	}

	OSAL_LIST_INIT(&p_hwfn->db_recovery_info.list);
#ifdef CONFIG_ECORE_LOCK_ALLOC
	if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_hwfn->db_recovery_info.lock))
		return ECORE_NOMEM;
#endif
	OSAL_SPIN_LOCK_INIT(&p_hwfn->db_recovery_info.lock);
	p_hwfn->db_recovery_info.db_recovery_counter = 0;

	return ECORE_SUCCESS;
}