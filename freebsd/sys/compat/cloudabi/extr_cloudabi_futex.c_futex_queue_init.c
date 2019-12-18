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
struct futex_queue {scalar_t__ fq_count; int /*<<< orphan*/  fq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
futex_queue_init(struct futex_queue *fq)
{

	STAILQ_INIT(&fq->fq_list);
	fq->fq_count = 0;
}