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
struct ecore_spq_entry {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_spq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ecore_spq_return_entry (struct ecore_hwfn*,struct ecore_spq_entry*) ; 

void ecore_spq_return_entry(struct ecore_hwfn *p_hwfn,
			    struct ecore_spq_entry *p_ent)
{
	OSAL_SPIN_LOCK(&p_hwfn->p_spq->lock);
	__ecore_spq_return_entry(p_hwfn, p_ent);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_spq->lock);
}