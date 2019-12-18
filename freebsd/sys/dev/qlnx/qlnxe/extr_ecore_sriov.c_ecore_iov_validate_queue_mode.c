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
typedef  size_t u16 ;
struct ecore_vf_queue_cid {scalar_t__ p_cid; int b_is_tx; } ;
struct ecore_vf_info {TYPE_1__* vf_queues; } ;
typedef  enum ecore_iov_validate_q_mode { ____Placeholder_ecore_iov_validate_q_mode } ecore_iov_validate_q_mode ;
struct TYPE_2__ {struct ecore_vf_queue_cid* cids; } ;

/* Variables and functions */
 int ECORE_IOV_VALIDATE_Q_DISABLE ; 
 int ECORE_IOV_VALIDATE_Q_ENABLE ; 
 int ECORE_IOV_VALIDATE_Q_NA ; 
 int MAX_QUEUES_PER_QZONE ; 
 scalar_t__ OSAL_NULL ; 

__attribute__((used)) static bool ecore_iov_validate_queue_mode(struct ecore_vf_info *p_vf,
					  u16 qid,
					  enum ecore_iov_validate_q_mode mode,
					  bool b_is_tx)
{
	int i;

	if (mode == ECORE_IOV_VALIDATE_Q_NA)
		return true;

	for (i = 0; i < MAX_QUEUES_PER_QZONE; i++) {
		struct ecore_vf_queue_cid *p_qcid;

		p_qcid = &p_vf->vf_queues[qid].cids[i];

		if (p_qcid->p_cid == OSAL_NULL)
			continue;

		if (p_qcid->b_is_tx != b_is_tx)
			continue;

		/* Found. It's enabled. */
		return (mode == ECORE_IOV_VALIDATE_Q_ENABLE);
	}

	/* In case we haven't found any valid cid, then its disabled */
	return (mode == ECORE_IOV_VALIDATE_Q_DISABLE);
}