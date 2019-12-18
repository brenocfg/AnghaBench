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
struct rsocket {int /*<<< orphan*/ * qp_list; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;
struct ds_qp {TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlist_remove (TYPE_1__*) ; 
 int /*<<< orphan*/ * ds_next_qp (struct ds_qp*) ; 

__attribute__((used)) static void ds_remove_qp(struct rsocket *rs, struct ds_qp *qp)
{
	if (qp->list.next != &qp->list) {
		rs->qp_list = ds_next_qp(qp);
		dlist_remove(&qp->list);
	} else {
		rs->qp_list = NULL;
	}
}