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
struct umtx_q {int /*<<< orphan*/  uq_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtxq_getchain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int /*<<< orphan*/  wakeup (struct umtx_q*) ; 

__attribute__((used)) static inline void
umtxq_signal_thread(struct umtx_q *uq)
{

	UMTXQ_LOCKED_ASSERT(umtxq_getchain(&uq->uq_key));
	umtxq_remove(uq);
	wakeup(uq);
}