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
struct mtx {int dummy; } ;
struct icl_conn {char const* ic_name; int ic_iser; int ic_unmapped; int /*<<< orphan*/  ic_offload; struct mtx* ic_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  flush_cv; int /*<<< orphan*/  flush_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ beacon; } ;
struct iser_conn {struct icl_conn icl_conn; TYPE_2__ ib_conn; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  up_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_ERR (char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ICL_ISER ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  icl_iser_class ; 
 int /*<<< orphan*/  icl_iser_ncons ; 
 scalar_t__ kobj_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct icl_conn *
iser_new_conn(const char *name, struct mtx *lock)
{
	struct iser_conn *iser_conn;
	struct icl_conn *ic;

	refcount_acquire(&icl_iser_ncons);

	iser_conn = (struct iser_conn *)kobj_create(&icl_iser_class, M_ICL_ISER, M_WAITOK | M_ZERO);
	if (!iser_conn) {
		ISER_ERR("failed to allocate iser conn");
		refcount_release(&icl_iser_ncons);
		return (NULL);
	}

	cv_init(&iser_conn->up_cv, "iser_cv");
	sx_init(&iser_conn->state_mutex, "iser_conn_state_mutex");
	mtx_init(&iser_conn->ib_conn.beacon.flush_lock, "iser_flush_lock", NULL, MTX_DEF);
	cv_init(&iser_conn->ib_conn.beacon.flush_cv, "flush_cv");
	mtx_init(&iser_conn->ib_conn.lock, "iser_lock", NULL, MTX_DEF);

	ic = &iser_conn->icl_conn;
	ic->ic_lock = lock;
	ic->ic_name = name;
	ic->ic_offload = strdup("iser", M_TEMP);
	ic->ic_iser = true;
	ic->ic_unmapped = true;

	return (ic);
}