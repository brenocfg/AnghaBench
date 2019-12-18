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
struct scatterlist {unsigned int length; } ;
struct scatter_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int SEMIBSIZE ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static void crypto_kw_scatterlist_ff(struct scatter_walk *walk,
				     struct scatterlist *sg,
				     unsigned int end)
{
	unsigned int skip = 0;

	/* The caller should only operate on full SEMIBLOCKs. */
	BUG_ON(end < SEMIBSIZE);

	skip = end - SEMIBSIZE;
	while (sg) {
		if (sg->length > skip) {
			scatterwalk_start(walk, sg);
			scatterwalk_advance(walk, skip);
			break;
		} else
			skip -= sg->length;

		sg = sg_next(sg);
	}
}