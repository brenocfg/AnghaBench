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
struct futex_waiter {struct futex_queue* fw_queue; } ;
struct futex_queue {int /*<<< orphan*/  fq_count; int /*<<< orphan*/  fq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct futex_waiter* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct futex_waiter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_next ; 

__attribute__((used)) static void
futex_queue_requeue(struct futex_queue *fqfrom, struct futex_queue *fqto,
    unsigned int nwaiters)
{
	struct futex_waiter *fw;

	/* Move waiters to the target queue. */
	while (nwaiters-- > 0 && !STAILQ_EMPTY(&fqfrom->fq_list)) {
		fw = STAILQ_FIRST(&fqfrom->fq_list);
		STAILQ_REMOVE_HEAD(&fqfrom->fq_list, fw_next);
		--fqfrom->fq_count;

		fw->fw_queue = fqto;
		STAILQ_INSERT_TAIL(&fqto->fq_list, fw, fw_next);
		++fqto->fq_count;
	}
}