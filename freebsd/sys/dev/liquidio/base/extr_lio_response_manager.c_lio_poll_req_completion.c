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
struct octeon_device {int dummy; } ;
struct lio_tq {int /*<<< orphan*/  work; int /*<<< orphan*/  tq; scalar_t__ ctxptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_ms_to_ticks (int) ; 
 int /*<<< orphan*/  lio_process_ordered_list (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_poll_req_completion(void *arg, int pending)
{
	struct lio_tq		*ctq = (struct lio_tq *)arg;
	struct octeon_device	*oct = (struct octeon_device *)ctq->ctxptr;

	lio_process_ordered_list(oct, 0);
	taskqueue_enqueue_timeout(ctq->tq, &ctq->work, lio_ms_to_ticks(50));
}