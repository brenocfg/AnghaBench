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
struct mtx {int dummy; } ;
struct icl_conn {char const* ic_name; char* ic_offload; int ic_unmapped; int /*<<< orphan*/  ic_max_data_segment_length; int /*<<< orphan*/  ic_outstanding_pdus; int /*<<< orphan*/  ic_receive_cv; int /*<<< orphan*/  ic_send_cv; struct mtx* ic_lock; int /*<<< orphan*/  ic_to_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_MAX_DATA_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  M_ICL_SOFT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  icl_ncons ; 
 int /*<<< orphan*/  icl_soft_class ; 
 scalar_t__ kobj_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct icl_conn *
icl_soft_new_conn(const char *name, struct mtx *lock)
{
	struct icl_conn *ic;

	refcount_acquire(&icl_ncons);

	ic = (struct icl_conn *)kobj_create(&icl_soft_class, M_ICL_SOFT, M_WAITOK | M_ZERO);

	STAILQ_INIT(&ic->ic_to_send);
	ic->ic_lock = lock;
	cv_init(&ic->ic_send_cv, "icl_tx");
	cv_init(&ic->ic_receive_cv, "icl_rx");
#ifdef DIAGNOSTIC
	refcount_init(&ic->ic_outstanding_pdus, 0);
#endif
	ic->ic_max_data_segment_length = ICL_MAX_DATA_SEGMENT_LENGTH;
	ic->ic_name = name;
	ic->ic_offload = "None";
	ic->ic_unmapped = false;

	return (ic);
}