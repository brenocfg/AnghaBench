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
struct TYPE_5__ {char* tl_offset; int /*<<< orphan*/  tl_lock; TYPE_1__** tl_head; int /*<<< orphan*/  tl_spa; } ;
typedef  TYPE_2__ txg_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TXG_MASK ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_verify (int /*<<< orphan*/ ,int) ; 

void *
txg_list_remove(txg_list_t *tl, uint64_t txg)
{
	int t = txg & TXG_MASK;
	txg_node_t *tn;
	void *p = NULL;

	txg_verify(tl->tl_spa, txg);
	mutex_enter(&tl->tl_lock);
	if ((tn = tl->tl_head[t]) != NULL) {
		ASSERT(tn->tn_member[t]);
		ASSERT(tn->tn_next[t] == NULL || tn->tn_next[t]->tn_member[t]);
		p = (char *)tn - tl->tl_offset;
		tl->tl_head[t] = tn->tn_next[t];
		tn->tn_next[t] = NULL;
		tn->tn_member[t] = 0;
	}
	mutex_exit(&tl->tl_lock);

	return (p);
}