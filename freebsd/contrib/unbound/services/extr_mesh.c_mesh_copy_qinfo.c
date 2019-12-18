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
typedef  int /*<<< orphan*/  uint16_t ;
struct regional {int dummy; } ;
struct query_info {int qname_len; int /*<<< orphan*/ * qname; } ;
struct TYPE_4__ {int /*<<< orphan*/  query_flags; int /*<<< orphan*/  qinfo; TYPE_1__* env; } ;
struct mesh_state {TYPE_2__ s; } ;
struct TYPE_3__ {struct regional* scratch; } ;

/* Variables and functions */
 void* regional_alloc_init (struct regional*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mesh_copy_qinfo(struct mesh_state* mstate, struct query_info** qinfop,
	uint16_t* qflags)
{
	struct regional* region = mstate->s.env->scratch;
	struct query_info* qinfo;

	qinfo = regional_alloc_init(region, &mstate->s.qinfo, sizeof(*qinfo));
	if(!qinfo)
		return;
	qinfo->qname = regional_alloc_init(region, qinfo->qname,
		qinfo->qname_len);
	if(!qinfo->qname)
		return;
	*qinfop = qinfo;
	*qflags = mstate->s.query_flags;
}