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
struct scatterlist {scalar_t__ length; } ;
struct request_queue {int dummy; } ;
struct bio_vec {int bv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  biovec_phys_mergeable (struct request_queue*,struct bio_vec*,struct bio_vec*) ; 
 scalar_t__ queue_max_segment_size (struct request_queue*) ; 

__attribute__((used)) static inline bool
__blk_segment_map_sg_merge(struct request_queue *q, struct bio_vec *bvec,
			   struct bio_vec *bvprv, struct scatterlist **sg)
{

	int nbytes = bvec->bv_len;

	if (!*sg)
		return false;

	if ((*sg)->length + nbytes > queue_max_segment_size(q))
		return false;

	if (!biovec_phys_mergeable(q, bvprv, bvec))
		return false;

	(*sg)->length += nbytes;

	return true;
}