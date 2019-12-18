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
struct ipfw_flow_id {int dummy; } ;
struct TYPE_2__ {struct ipfw_flow_id fid; } ;
struct dn_sch_inst {TYPE_1__ ni; } ;

/* Variables and functions */
 int DNHT_KEY_IS_OBJ ; 
 scalar_t__ flow_id_cmp (struct ipfw_flow_id*,struct ipfw_flow_id*) ; 

__attribute__((used)) static int
si_match(void *obj, uintptr_t key, int flags, void *arg)
{
	struct dn_sch_inst *o = obj;
	struct ipfw_flow_id *id2;

	id2 = (flags & DNHT_KEY_IS_OBJ) ?
		&((struct dn_sch_inst *)key)->ni.fid :
		(struct ipfw_flow_id *)key;
	return flow_id_cmp(&o->ni.fid,  id2) == 0;
}