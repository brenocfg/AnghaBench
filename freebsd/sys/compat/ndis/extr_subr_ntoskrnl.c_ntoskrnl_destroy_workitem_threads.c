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
struct TYPE_5__ {int kq_exit; TYPE_1__* kq_td; int /*<<< orphan*/  kq_proc; } ;
typedef  TYPE_2__ kdpc_queue ;
struct TYPE_4__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWAIT ; 
 int WORKITEM_THREADS ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* wq_queues ; 

__attribute__((used)) static void
ntoskrnl_destroy_workitem_threads(void)
{
	kdpc_queue		*kq;
	int			i;

	for (i = 0; i < WORKITEM_THREADS; i++) {
		kq = wq_queues + i;
		kq->kq_exit = 1;
		KeSetEvent(&kq->kq_proc, IO_NO_INCREMENT, FALSE);
		while (kq->kq_exit)
			tsleep(kq->kq_td->td_proc, PWAIT, "waitiw", hz/10);
	}
}