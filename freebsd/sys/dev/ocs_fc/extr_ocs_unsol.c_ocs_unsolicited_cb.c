#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_16__ {TYPE_3__* rq_thread_info; } ;
typedef  TYPE_4__ ocs_xport_t ;
struct TYPE_17__ {scalar_t__ rq_threads; int /*<<< orphan*/  hw; TYPE_4__* xport; } ;
typedef  TYPE_5__ ocs_t ;
struct TYPE_18__ {TYPE_2__* header; } ;
typedef  TYPE_6__ ocs_hw_sequence_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_19__ {int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_7__ fc_header_t ;
struct TYPE_15__ {int /*<<< orphan*/  seq_cbuf; } ;
struct TYPE_13__ {TYPE_7__* virt; } ;
struct TYPE_14__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUTRACE (char*) ; 
 size_t ocs_be16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_cbuf_put (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ocs_hw_sequence_free (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ ocs_unsol_process (TYPE_5__*,TYPE_6__*) ; 

int32_t
ocs_unsolicited_cb(void *arg, ocs_hw_sequence_t *seq)
{
	ocs_t *ocs = arg;
	ocs_xport_t *xport = ocs->xport;
	int32_t rc;

	CPUTRACE("");

	if (ocs->rq_threads == 0) {
		rc = ocs_unsol_process(ocs, seq);
	} else {
		/* use the ox_id to dispatch this IO to a thread */
		fc_header_t *hdr = seq->header->dma.virt;
		uint32_t ox_id =  ocs_be16toh(hdr->ox_id);
		uint32_t thr_index = ox_id % ocs->rq_threads;

		rc = ocs_cbuf_put(xport->rq_thread_info[thr_index].seq_cbuf, seq);
	}

	if (rc) {
		ocs_hw_sequence_free(&ocs->hw, seq);
	}

	return 0;
}