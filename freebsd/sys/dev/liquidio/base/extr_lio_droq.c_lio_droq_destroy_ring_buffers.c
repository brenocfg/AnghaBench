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
typedef  size_t uint32_t ;
struct octeon_device {int dummy; } ;
struct lio_droq {size_t max_count; TYPE_1__* recv_buf_list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_droq_reset_indices (struct lio_droq*) ; 
 int /*<<< orphan*/  lio_recv_buffer_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lio_droq_destroy_ring_buffers(struct octeon_device *oct,
			      struct lio_droq *droq)
{
	uint32_t	i;

	for (i = 0; i < droq->max_count; i++) {
		if (droq->recv_buf_list[i].buffer != NULL) {
			lio_recv_buffer_free(droq->recv_buf_list[i].buffer);
			droq->recv_buf_list[i].buffer = NULL;
		}
	}

	lio_droq_reset_indices(droq);
}