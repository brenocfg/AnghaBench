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
struct scatterlist {int dummy; } ;
struct dsgl_walk {unsigned int nents; int last_sg_len; struct scatterlist* last_sg; TYPE_1__* to; } ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; int /*<<< orphan*/ * len; } ;

/* Variables and functions */
 int CHCR_DST_SG_SIZE ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  htons (int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void  dsgl_walk_add_sg(struct dsgl_walk *walk,
			   struct scatterlist *sg,
			      unsigned int slen,
			      unsigned int skip)
{
	int skip_len = 0;
	unsigned int left_size = slen, len = 0;
	unsigned int j = walk->nents;
	int offset, ent_len;

	if (!slen)
		return;
	while (sg && skip) {
		if (sg_dma_len(sg) <= skip) {
			skip -= sg_dma_len(sg);
			skip_len = 0;
			sg = sg_next(sg);
		} else {
			skip_len = skip;
			skip = 0;
		}
	}

	while (left_size && sg) {
		len = min_t(u32, left_size, sg_dma_len(sg) - skip_len);
		offset = 0;
		while (len) {
			ent_len =  min_t(u32, len, CHCR_DST_SG_SIZE);
			walk->to->len[j % 8] = htons(ent_len);
			walk->to->addr[j % 8] = cpu_to_be64(sg_dma_address(sg) +
						      offset + skip_len);
			offset += ent_len;
			len -= ent_len;
			j++;
			if ((j % 8) == 0)
				walk->to++;
		}
		walk->last_sg = sg;
		walk->last_sg_len = min_t(u32, left_size, sg_dma_len(sg) -
					  skip_len) + skip_len;
		left_size -= min_t(u32, left_size, sg_dma_len(sg) - skip_len);
		skip_len = 0;
		sg = sg_next(sg);
	}
	walk->nents = j;
}