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
struct TYPE_3__ {int /*<<< orphan*/  max_write_same_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;
struct p_sizes {TYPE_2__* qlim; } ;
struct drbd_device {struct request_queue* rq_queue; } ;
struct TYPE_4__ {int write_same_capable; scalar_t__ discard_enabled; void* io_opt; void* io_min; void* alignment_offset; void* logical_block_size; void* physical_block_size; } ;

/* Variables and functions */
 scalar_t__ blk_queue_discard (struct request_queue*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_alignment_offset (struct request_queue*) ; 
 int /*<<< orphan*/  queue_io_min (struct request_queue*) ; 
 int /*<<< orphan*/  queue_io_opt (struct request_queue*) ; 
 int /*<<< orphan*/  queue_logical_block_size (struct request_queue*) ; 
 int /*<<< orphan*/  queue_physical_block_size (struct request_queue*) ; 

__attribute__((used)) static void
assign_p_sizes_qlim(struct drbd_device *device, struct p_sizes *p,
					struct request_queue *q)
{
	if (q) {
		p->qlim->physical_block_size = cpu_to_be32(queue_physical_block_size(q));
		p->qlim->logical_block_size = cpu_to_be32(queue_logical_block_size(q));
		p->qlim->alignment_offset = cpu_to_be32(queue_alignment_offset(q));
		p->qlim->io_min = cpu_to_be32(queue_io_min(q));
		p->qlim->io_opt = cpu_to_be32(queue_io_opt(q));
		p->qlim->discard_enabled = blk_queue_discard(q);
		p->qlim->write_same_capable = !!q->limits.max_write_same_sectors;
	} else {
		q = device->rq_queue;
		p->qlim->physical_block_size = cpu_to_be32(queue_physical_block_size(q));
		p->qlim->logical_block_size = cpu_to_be32(queue_logical_block_size(q));
		p->qlim->alignment_offset = 0;
		p->qlim->io_min = cpu_to_be32(queue_io_min(q));
		p->qlim->io_opt = cpu_to_be32(queue_io_opt(q));
		p->qlim->discard_enabled = 0;
		p->qlim->write_same_capable = 0;
	}
}