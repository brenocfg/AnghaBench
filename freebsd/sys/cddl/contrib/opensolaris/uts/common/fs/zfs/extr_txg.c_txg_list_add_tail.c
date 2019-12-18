#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {int* tn_member; struct TYPE_4__** tn_next; } ;
typedef  TYPE_1__ txg_node_t ;
struct TYPE_5__ {int tl_offset; int /*<<< orphan*/  tl_lock; TYPE_1__** tl_head; int /*<<< orphan*/  tl_spa; } ;
typedef  TYPE_2__ txg_list_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int TXG_MASK ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_verify (int /*<<< orphan*/ ,int) ; 

boolean_t
txg_list_add_tail(txg_list_t *tl, void *p, uint64_t txg)
{
	int t = txg & TXG_MASK;
	txg_node_t *tn = (txg_node_t *)((char *)p + tl->tl_offset);
	boolean_t add;

	txg_verify(tl->tl_spa, txg);
	mutex_enter(&tl->tl_lock);
	add = (tn->tn_member[t] == 0);
	if (add) {
		txg_node_t **tp;

		for (tp = &tl->tl_head[t]; *tp != NULL; tp = &(*tp)->tn_next[t])
			continue;

		tn->tn_member[t] = 1;
		tn->tn_next[t] = NULL;
		*tp = tn;
	}
	mutex_exit(&tl->tl_lock);

	return (add);
}