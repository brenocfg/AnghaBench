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
struct serviced_query {TYPE_1__* outnet; int /*<<< orphan*/  to_be_deleted; int /*<<< orphan*/  cblist; } ;
struct TYPE_2__ {int /*<<< orphan*/  serviced; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_list_remove (struct serviced_query*,void*) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ ,struct serviced_query*) ; 
 int /*<<< orphan*/  serviced_delete (struct serviced_query*) ; 

void outnet_serviced_query_stop(struct serviced_query* sq, void* cb_arg)
{
	if(!sq) 
		return;
	callback_list_remove(sq, cb_arg);
	/* if callbacks() routine scheduled deletion, let it do that */
	if(!sq->cblist && !sq->to_be_deleted) {
		(void)rbtree_delete(sq->outnet->serviced, sq);
		serviced_delete(sq); 
	}
}