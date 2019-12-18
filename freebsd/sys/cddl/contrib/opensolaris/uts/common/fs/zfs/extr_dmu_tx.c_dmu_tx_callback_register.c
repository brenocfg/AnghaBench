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
struct TYPE_6__ {int /*<<< orphan*/  tx_callbacks; } ;
typedef  TYPE_1__ dmu_tx_t ;
struct TYPE_7__ {void* dcb_data; int /*<<< orphan*/ * dcb_func; } ;
typedef  TYPE_2__ dmu_tx_callback_t ;
typedef  int /*<<< orphan*/  dmu_tx_callback_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
dmu_tx_callback_register(dmu_tx_t *tx, dmu_tx_callback_func_t *func, void *data)
{
	dmu_tx_callback_t *dcb;

	dcb = kmem_alloc(sizeof (dmu_tx_callback_t), KM_SLEEP);

	dcb->dcb_func = func;
	dcb->dcb_data = data;

	list_insert_tail(&tx->tx_callbacks, dcb);
}