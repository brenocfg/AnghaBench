#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rsocket {struct ds_qp* qp_list; } ;
struct ds_qp {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds_insert_qp(struct rsocket *rs, struct ds_qp *qp)
{
	if (!rs->qp_list)
		dlist_init(&qp->list);
	else
		dlist_insert_head(&qp->list, &rs->qp_list->list);
	rs->qp_list = qp;
}