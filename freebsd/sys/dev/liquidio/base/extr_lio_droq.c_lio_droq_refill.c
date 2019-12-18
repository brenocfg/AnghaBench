#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct octeon_device {int /*<<< orphan*/  device; } ;
struct mbuf {int /*<<< orphan*/ * m_data; } ;
struct lio_droq_desc {int /*<<< orphan*/  buffer_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_alloc_failure; } ;
struct lio_droq {scalar_t__ max_count; size_t refill_idx; scalar_t__ refill_count; int /*<<< orphan*/  buffer_size; TYPE_2__* recv_buf_list; TYPE_1__ stats; struct lio_droq_desc* desc_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ lio_droq_refill_pullup_descs (struct lio_droq*,struct lio_droq_desc*) ; 
 size_t lio_incr_index (size_t,int,scalar_t__) ; 
 int /*<<< orphan*/  lio_map_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* lio_recv_buffer_alloc (int /*<<< orphan*/ ) ; 

uint32_t
lio_droq_refill(struct octeon_device *octeon_dev, struct lio_droq *droq)
{
	struct lio_droq_desc	*desc_ring;
	void			*buf = NULL;
	uint32_t		desc_refilled = 0;
	uint8_t			*data;

	desc_ring = droq->desc_ring;

	while (droq->refill_count && (desc_refilled < droq->max_count)) {
		/*
		 * If a valid buffer exists (happens if there is no dispatch),
		 * reuse
		 * the buffer, else allocate.
		 */
		if (droq->recv_buf_list[droq->refill_idx].buffer == NULL) {
			buf = lio_recv_buffer_alloc(droq->buffer_size);
			/*
			 * If a buffer could not be allocated, no point in
			 * continuing
			 */
			if (buf == NULL) {
				droq->stats.rx_alloc_failure++;
				break;
			}

			droq->recv_buf_list[droq->refill_idx].buffer = buf;
			data = ((struct mbuf *)buf)->m_data;
		} else {
			data = ((struct mbuf *)droq->recv_buf_list
				[droq->refill_idx].buffer)->m_data;
		}

		droq->recv_buf_list[droq->refill_idx].data = data;

		desc_ring[droq->refill_idx].buffer_ptr =
		    lio_map_ring(octeon_dev->device,
				 droq->recv_buf_list[droq->refill_idx].buffer,
				 droq->buffer_size);

		droq->refill_idx = lio_incr_index(droq->refill_idx, 1,
						  droq->max_count);
		desc_refilled++;
		droq->refill_count--;
	}

	if (droq->refill_count)
		desc_refilled += lio_droq_refill_pullup_descs(droq, desc_ring);

	/*
	 * if droq->refill_count
	 * The refill count would not change in pass two. We only moved buffers
	 * to close the gap in the ring, but we would still have the same no. of
	 * buffers to refill.
	 */
	return (desc_refilled);
}