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

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 

__attribute__((used)) static inline struct scatterlist *create_multi_sg(struct scatterlist *to_sg,
						  struct scatterlist *from_sg,
						  int buflen)
{
	struct scatterlist *sg = to_sg;
	unsigned int sglen;

	for (; buflen && from_sg; buflen -= sglen) {
		sglen = from_sg->length;
		if (sglen > buflen)
			sglen = buflen;

		sg_set_buf(sg, sg_virt(from_sg), sglen);
		from_sg = sg_next(from_sg);
		sg++;
	}

	return sg;
}