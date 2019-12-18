#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dn_sch_inst {TYPE_2__* sched; int /*<<< orphan*/  ni; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct dn_flow {TYPE_3__ oid; } ;
struct copy_args {int /*<<< orphan*/  end; scalar_t__* start; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched_nr; } ;
struct TYPE_5__ {TYPE_1__ sch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNHT_KEY_IS_OBJ ; 
 int DNHT_SCAN_END ; 
 int /*<<< orphan*/  DN_FLOW ; 
 scalar_t__ copy_obj (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_hash (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
copy_si_cb(void *obj, void *arg)
{
	struct dn_sch_inst *si = obj;
	struct copy_args *a = arg;
	struct dn_flow *ni = (struct dn_flow *)(*a->start);
	if (copy_obj(a->start, a->end, &si->ni, "inst",
			si->sched->sch.sched_nr))
		return DNHT_SCAN_END;
	ni->oid.type = DN_FLOW; /* override the DN_SCH_I */
	ni->oid.id = si_hash((uintptr_t)si, DNHT_KEY_IS_OBJ, NULL);
	return 0;
}