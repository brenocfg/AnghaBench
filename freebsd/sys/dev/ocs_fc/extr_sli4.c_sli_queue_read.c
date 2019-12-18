#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ sli4_t ;
struct TYPE_11__ {int /*<<< orphan*/ * virt; } ;
struct TYPE_8__ {int r_idx; } ;
struct TYPE_10__ {int type; int index; int size; int /*<<< orphan*/  lock; int /*<<< orphan*/  n_posted; int /*<<< orphan*/  length; TYPE_7__ dma; TYPE_1__ u; } ;
typedef  TYPE_3__ sli4_queue_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_DEBUG_ENABLE_CQ_DUMP ; 
 int /*<<< orphan*/  OCS_DEBUG_ENABLE_EQ_DUMP ; 
 int /*<<< orphan*/  OCS_DEBUG_ENABLE_MQ_DUMP ; 
 int /*<<< orphan*/  OCS_DMASYNC_POSTREAD ; 
#define  SLI_QTYPE_CQ 130 
#define  SLI_QTYPE_EQ 129 
#define  SLI_QTYPE_MQ 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_dma_sync (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_dump32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_queue_entry_is_valid (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t
sli_queue_read(sli4_t *sli4, sli4_queue_t *q, uint8_t *entry)
{
	int32_t		rc = 0;
	uint8_t		*qe = q->dma.virt;
	uint32_t	*qindex = NULL;

	if (SLI_QTYPE_MQ == q->type) {
		qindex = &q->u.r_idx;
	} else {
		qindex = &q->index;
	}

	ocs_lock(&q->lock);

	ocs_dma_sync(&q->dma, OCS_DMASYNC_POSTREAD);

	qe += *qindex * q->size;

	if (!sli_queue_entry_is_valid(q, qe, TRUE)) {
		ocs_unlock(&q->lock);
		return -1;
	}

	if (entry) {
		ocs_memcpy(entry, qe, q->size);
#if defined(OCS_INCLUDE_DEBUG)
		switch(q->type) {
		case SLI_QTYPE_CQ:
			ocs_dump32(OCS_DEBUG_ENABLE_CQ_DUMP, sli4->os, "cq", entry, q->size);
			break;
		case SLI_QTYPE_MQ:
			ocs_dump32(OCS_DEBUG_ENABLE_MQ_DUMP, sli4->os, "mq Compl", entry, 64);
			break;
		case SLI_QTYPE_EQ:
			ocs_dump32(OCS_DEBUG_ENABLE_EQ_DUMP, sli4->os, "eq Compl", entry, q->size);
			break;
		default:
			break;
		}
#endif
	}

	switch (q->type) {
		case SLI_QTYPE_EQ:
		case SLI_QTYPE_CQ:
		case SLI_QTYPE_MQ:
			*qindex = (*qindex + 1) & (q->length - 1);
			if (SLI_QTYPE_MQ != q->type) {
				q->n_posted++;
			}
			break;
		default:
			/* reads don't update the index */
			break;
	}

	ocs_unlock(&q->lock);

	return rc;
}