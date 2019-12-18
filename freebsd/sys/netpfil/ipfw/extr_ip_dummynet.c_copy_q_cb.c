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
struct dn_queue {int /*<<< orphan*/  ni; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct dn_flow {int /*<<< orphan*/  fid; TYPE_1__ oid; } ;
struct copy_args {int /*<<< orphan*/  end; scalar_t__* start; } ;

/* Variables and functions */
 int DNHT_SCAN_END ; 
 int /*<<< orphan*/  DN_FLOW ; 
 scalar_t__ copy_obj_q (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  si_hash (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
copy_q_cb(void *obj, void *arg)
{
	struct dn_queue *q = obj;
	struct copy_args *a = arg;
	struct dn_flow *ni = (struct dn_flow *)(*a->start);
        if (copy_obj_q(a->start, a->end, &q->ni, "queue", -1))
                return DNHT_SCAN_END;
        ni->oid.type = DN_FLOW; /* override the DN_QUEUE */
        ni->oid.id = si_hash((uintptr_t)&ni->fid, 0, NULL);
        return 0;
}