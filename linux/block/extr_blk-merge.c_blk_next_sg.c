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

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 

__attribute__((used)) static inline struct scatterlist *blk_next_sg(struct scatterlist **sg,
		struct scatterlist *sglist)
{
	if (!*sg)
		return sglist;

	/*
	 * If the driver previously mapped a shorter list, we could see a
	 * termination bit prematurely unless it fully inits the sg table
	 * on each mapping. We KNOW that there must be more entries here
	 * or the driver would be buggy, so force clear the termination bit
	 * to avoid doing a full sg_init_table() in drivers for each command.
	 */
	sg_unmark_end(*sg);
	return sg_next(*sg);
}