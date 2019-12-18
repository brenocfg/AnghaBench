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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  eh; } ;
typedef  TYPE_1__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushAdapter (TYPE_1__*) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
hpt_shutdown(device_t dev)
{
		IAL_ADAPTER_T *pAdapter;
	
		pAdapter = device_get_softc(dev);

		EVENTHANDLER_DEREGISTER(shutdown_final, pAdapter->eh);
		mtx_lock(&pAdapter->lock);
		FlushAdapter(pAdapter);
		mtx_unlock(&pAdapter->lock);
		  /* give the flush some time to happen, 
		    *otherwise "shutdown -p now" will make file system corrupted */
		DELAY(1000 * 1000 * 5);
		return 0;
}