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
struct request {int rq_flags; int /*<<< orphan*/  extra_len; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  nr_phys_segments; int /*<<< orphan*/  special_vec; int /*<<< orphan*/  __data_len; int /*<<< orphan*/  __sector; } ;

/* Variables and functions */
 int RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 

__attribute__((used)) static void __blk_rq_prep_clone(struct request *dst, struct request *src)
{
	dst->__sector = blk_rq_pos(src);
	dst->__data_len = blk_rq_bytes(src);
	if (src->rq_flags & RQF_SPECIAL_PAYLOAD) {
		dst->rq_flags |= RQF_SPECIAL_PAYLOAD;
		dst->special_vec = src->special_vec;
	}
	dst->nr_phys_segments = src->nr_phys_segments;
	dst->ioprio = src->ioprio;
	dst->extra_len = src->extra_len;
}