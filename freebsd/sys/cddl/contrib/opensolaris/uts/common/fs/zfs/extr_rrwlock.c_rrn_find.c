#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rr_linked_rcount; } ;
typedef  TYPE_1__ rrwlock_t ;
struct TYPE_7__ {TYPE_1__* rn_rrl; struct TYPE_7__* rn_next; } ;
typedef  TYPE_2__ rrw_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  rrw_tsd_key ; 
 TYPE_2__* tsd_get (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rrw_node_t *
rrn_find(rrwlock_t *rrl)
{
	rrw_node_t *rn;

	if (zfs_refcount_count(&rrl->rr_linked_rcount) == 0)
		return (NULL);

	for (rn = tsd_get(rrw_tsd_key); rn != NULL; rn = rn->rn_next) {
		if (rn->rn_rrl == rrl)
			return (rn);
	}
	return (NULL);
}