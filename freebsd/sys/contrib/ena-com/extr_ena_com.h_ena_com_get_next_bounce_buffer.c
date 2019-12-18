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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ena_com_io_bounce_buffer_control {int buffer_size; int buffers_num; int next_to_use; int /*<<< orphan*/ * base_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u8 *ena_com_get_next_bounce_buffer(struct ena_com_io_bounce_buffer_control *bounce_buf_ctrl)
{
	u16 size, buffers_num;
	u8 *buf;

	size = bounce_buf_ctrl->buffer_size;
	buffers_num = bounce_buf_ctrl->buffers_num;

	buf = bounce_buf_ctrl->base_buffer +
		(bounce_buf_ctrl->next_to_use++ & (buffers_num - 1)) * size;

	prefetchw(bounce_buf_ctrl->base_buffer +
		(bounce_buf_ctrl->next_to_use & (buffers_num - 1)) * size);

	return buf;
}