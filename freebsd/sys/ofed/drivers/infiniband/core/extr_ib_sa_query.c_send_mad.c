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
struct ib_sa_query {int id; int flags; TYPE_1__* mad_buf; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int timeout_ms; struct ib_sa_query** context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int IB_SA_ENABLE_LOCAL_SERVICE ; 
 int gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int ib_post_send_mad (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_sa_disable_local_svc (struct ib_sa_query*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ib_sa_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  query_idr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int send_mad(struct ib_sa_query *query, int timeout_ms, gfp_t gfp_mask)
{
	bool preload = gfpflags_allow_blocking(gfp_mask);
	unsigned long flags;
	int ret, id;

	if (preload)
		idr_preload(gfp_mask);
	spin_lock_irqsave(&idr_lock, flags);

	id = idr_alloc(&query_idr, query, 0, 0, GFP_NOWAIT);

	spin_unlock_irqrestore(&idr_lock, flags);
	if (preload)
		idr_preload_end();
	if (id < 0)
		return id;

	query->mad_buf->timeout_ms  = timeout_ms;
	query->mad_buf->context[0] = query;
	query->id = id;

	if (query->flags & IB_SA_ENABLE_LOCAL_SERVICE) {
		ib_sa_disable_local_svc(query);
	}

	ret = ib_post_send_mad(query->mad_buf, NULL);
	if (ret) {
		spin_lock_irqsave(&idr_lock, flags);
		idr_remove(&query_idr, id);
		spin_unlock_irqrestore(&idr_lock, flags);
	}

	/*
	 * It's not safe to dereference query any more, because the
	 * send may already have completed and freed the query in
	 * another context.
	 */
	return ret ? ret : id;
}