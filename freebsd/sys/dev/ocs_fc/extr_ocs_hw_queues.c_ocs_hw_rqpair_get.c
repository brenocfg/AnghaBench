#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  size_t uint16_t ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  index; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ sli4_queue_t ;
struct TYPE_9__ {size_t* hw_rq_lookup; int /*<<< orphan*/  os; int /*<<< orphan*/  sli; TYPE_3__** hw_rq; TYPE_1__* rq; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_sequence_t ;
struct TYPE_10__ {int id; int /*<<< orphan*/ ** rq_tracker; } ;
typedef  TYPE_3__ hw_rq_t ;

/* Variables and functions */
 int /*<<< orphan*/  _sli_queue_poke (int /*<<< orphan*/ *,TYPE_1__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,size_t,size_t,size_t,...) ; 
 int /*<<< orphan*/  sli_queue_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  sli_queue_unlock (TYPE_1__*) ; 

__attribute__((used)) static ocs_hw_sequence_t *
ocs_hw_rqpair_get(ocs_hw_t *hw, uint16_t rqindex, uint16_t bufindex)
{
	sli4_queue_t *rq_hdr = &hw->rq[rqindex];
	sli4_queue_t *rq_payload = &hw->rq[rqindex+1];
	ocs_hw_sequence_t *seq = NULL;
	hw_rq_t *rq = hw->hw_rq[hw->hw_rq_lookup[rqindex]];

#if defined(ENABLE_DEBUG_RQBUF)
	uint64_t rqbuf_debug_value = 0xdead0000 | ((rq->id & 0xf) << 12) | (bufindex & 0xfff);
#endif

	if (bufindex >= rq_hdr->length) {
		ocs_log_err(hw->os, "RQ index %d bufindex %d exceed ring length %d for id %d\n",
			    rqindex, bufindex, rq_hdr->length, rq_hdr->id);
		return NULL;
	}

	sli_queue_lock(rq_hdr);
	sli_queue_lock(rq_payload);

#if defined(ENABLE_DEBUG_RQBUF)
	/* Put a debug value into the rq, to track which entries are still valid */
	_sli_queue_poke(&hw->sli, rq_hdr, bufindex, (uint8_t *)&rqbuf_debug_value);
	_sli_queue_poke(&hw->sli, rq_payload, bufindex, (uint8_t *)&rqbuf_debug_value);
#endif

	seq = rq->rq_tracker[bufindex];
	rq->rq_tracker[bufindex] = NULL;

	if (seq == NULL ) {
		ocs_log_err(hw->os, "RQ buffer NULL, rqindex %d, bufindex %d, current q index = %d\n",
			    rqindex, bufindex, rq_hdr->index);
	}

	sli_queue_unlock(rq_payload);
	sli_queue_unlock(rq_hdr);
	return seq;
}