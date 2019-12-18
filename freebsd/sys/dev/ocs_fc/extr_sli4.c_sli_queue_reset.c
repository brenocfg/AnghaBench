#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_6__ {int /*<<< orphan*/ * virt; } ;
struct TYPE_5__ {scalar_t__ r_idx; } ;
struct TYPE_7__ {scalar_t__ type; int size; int /*<<< orphan*/  lock; scalar_t__ length; TYPE_2__ dma; TYPE_1__ u; scalar_t__ n_posted; scalar_t__ index; } ;
typedef  TYPE_3__ sli4_queue_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ SLI_QTYPE_MQ ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
sli_queue_reset(sli4_t *sli4, sli4_queue_t *q)
{

	ocs_lock(&q->lock);

	q->index = 0;
	q->n_posted = 0;

	if (SLI_QTYPE_MQ == q->type) {
		q->u.r_idx = 0;
	}

	if (q->dma.virt != NULL) {
		ocs_memset(q->dma.virt, 0, (q->size * (uint64_t)q->length));
	}

	ocs_unlock(&q->lock);

	return 0;
}