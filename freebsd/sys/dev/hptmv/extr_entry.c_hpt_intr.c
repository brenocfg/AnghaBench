#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  hpt_intr_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hpt_intr(void *arg)
{
	IAL_ADAPTER_T *pAdapter;

	pAdapter = arg;
	mtx_lock(&pAdapter->lock);
	hpt_intr_locked(pAdapter);
	mtx_unlock(&pAdapter->lock);
}