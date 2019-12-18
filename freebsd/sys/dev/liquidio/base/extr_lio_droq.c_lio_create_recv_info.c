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
typedef  void* uint16_t ;
struct octeon_device {scalar_t__ octeon_id; } ;
struct lio_recv_pkt {size_t length; size_t* buffer_size; int /*<<< orphan*/ ** buffer_ptr; void* octeon_id; void* buffer_count; int /*<<< orphan*/  rh; } ;
struct lio_recv_info {struct lio_recv_pkt* recv_pkt; } ;
struct lio_droq_info {scalar_t__ length; int /*<<< orphan*/  rh; } ;
struct lio_droq {size_t buffer_size; int /*<<< orphan*/  max_count; TYPE_1__* recv_buf_list; } ;
struct __dispatch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; scalar_t__ data; } ;

/* Variables and functions */
 struct lio_recv_info* lio_alloc_recv_info (int) ; 
 size_t lio_incr_index (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct lio_recv_info *
lio_create_recv_info(struct octeon_device *octeon_dev, struct lio_droq *droq,
		     uint32_t buf_cnt, uint32_t idx)
{
	struct lio_droq_info	*info;
	struct lio_recv_pkt	*recv_pkt;
	struct lio_recv_info	*recv_info;
	uint32_t		bytes_left, i;

	info = (struct lio_droq_info *)droq->recv_buf_list[idx].data;

	recv_info = lio_alloc_recv_info(sizeof(struct __dispatch));
	if (recv_info == NULL)
		return (NULL);

	recv_pkt = recv_info->recv_pkt;
	recv_pkt->rh = info->rh;
	recv_pkt->length = (uint32_t)info->length;
	recv_pkt->buffer_count = (uint16_t)buf_cnt;
	recv_pkt->octeon_id = (uint16_t)octeon_dev->octeon_id;

	i = 0;
	bytes_left = (uint32_t)info->length;

	while (buf_cnt) {
		recv_pkt->buffer_size[i] = (bytes_left >= droq->buffer_size) ?
			droq->buffer_size : bytes_left;

		recv_pkt->buffer_ptr[i] = droq->recv_buf_list[idx].buffer;
		droq->recv_buf_list[idx].buffer = NULL;

		idx = lio_incr_index(idx, 1, droq->max_count);
		bytes_left -= droq->buffer_size;
		i++;
		buf_cnt--;
	}

	return (recv_info);
}