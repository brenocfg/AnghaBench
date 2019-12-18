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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipfw_flow_id {int dummy; } ;
struct TYPE_2__ {struct ipfw_flow_id fid; } ;
struct dn_queue {TYPE_1__ ni; } ;

/* Variables and functions */
 int DNHT_KEY_IS_OBJ ; 
 int /*<<< orphan*/  flow_id_hash (struct ipfw_flow_id*) ; 

__attribute__((used)) static uint32_t
q_hash(uintptr_t key, int flags, void *arg)
{
	/* compute the hash slot from the flow id */
	struct ipfw_flow_id *id = (flags & DNHT_KEY_IS_OBJ) ?
		&((struct dn_queue *)key)->ni.fid :
		(struct ipfw_flow_id *)key;

	return flow_id_hash(id);
}