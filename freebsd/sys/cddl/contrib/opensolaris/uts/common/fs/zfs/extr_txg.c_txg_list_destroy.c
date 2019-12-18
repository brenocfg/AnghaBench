#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tl_lock; } ;
typedef  TYPE_1__ txg_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_list_empty (TYPE_1__*,int) ; 

void
txg_list_destroy(txg_list_t *tl)
{
	int t;

	for (t = 0; t < TXG_SIZE; t++)
		ASSERT(txg_list_empty(tl, t));

	mutex_destroy(&tl->tl_lock);
}