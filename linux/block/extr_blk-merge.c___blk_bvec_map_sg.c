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
struct scatterlist {int dummy; } ;
struct bio_vec {int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 struct scatterlist* blk_next_sg (struct scatterlist**,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __blk_bvec_map_sg(struct bio_vec bv,
		struct scatterlist *sglist, struct scatterlist **sg)
{
	*sg = blk_next_sg(sg, sglist);
	sg_set_page(*sg, bv.bv_page, bv.bv_len, bv.bv_offset);
	return 1;
}