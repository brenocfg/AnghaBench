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
struct kobj {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  flush_cv; } ;
struct TYPE_4__ {TYPE_1__ beacon; int /*<<< orphan*/  lock; } ;
struct iser_conn {int /*<<< orphan*/  up_cv; int /*<<< orphan*/  state_mutex; TYPE_2__ ib_conn; } ;
struct icl_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ICL_ISER ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_iser_ncons ; 
 struct iser_conn* icl_to_iser_conn (struct icl_conn*) ; 
 int /*<<< orphan*/  iser_conn_release (struct icl_conn*) ; 
 int /*<<< orphan*/  kobj_delete (struct kobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void
iser_conn_free(struct icl_conn *ic)
{
	struct iser_conn *iser_conn = icl_to_iser_conn(ic);

	iser_conn_release(ic);
	mtx_destroy(&iser_conn->ib_conn.lock);
	cv_destroy(&iser_conn->ib_conn.beacon.flush_cv);
	mtx_destroy(&iser_conn->ib_conn.beacon.flush_lock);
	sx_destroy(&iser_conn->state_mutex);
	cv_destroy(&iser_conn->up_cv);
	kobj_delete((struct kobj *)iser_conn, M_ICL_ISER);
	refcount_release(&icl_iser_ncons);
}