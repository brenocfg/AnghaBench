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
struct ena_que {int /*<<< orphan*/  cleanup_task; int /*<<< orphan*/  cleanup_tq; struct ena_adapter* adapter; } ;
struct ena_adapter {int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int IFF_DRV_RUNNING ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_handle_msix(void *arg)
{
	struct ena_que *queue = arg;
	struct ena_adapter *adapter = queue->adapter;
	if_t ifp = adapter->ifp;

	if (unlikely((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0))
		return (FILTER_STRAY);

	taskqueue_enqueue(queue->cleanup_tq, &queue->cleanup_task);

	return (FILTER_HANDLED);
}