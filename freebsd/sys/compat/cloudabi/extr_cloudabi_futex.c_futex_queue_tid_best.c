#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct futex_queue {int /*<<< orphan*/  fq_list; } ;
typedef  int /*<<< orphan*/  cloudabi_tid_t ;
struct TYPE_2__ {int /*<<< orphan*/  fw_tid; } ;

/* Variables and functions */
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static cloudabi_tid_t
futex_queue_tid_best(const struct futex_queue *fq)
{

	return (STAILQ_FIRST(&fq->fq_list)->fw_tid);
}