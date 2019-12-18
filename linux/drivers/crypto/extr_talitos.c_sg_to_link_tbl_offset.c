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
struct talitos_ptr {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_PTR_LNKTBL_RET ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  to_talitos_ptr (struct talitos_ptr*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_talitos_ptr_ext_set (struct talitos_ptr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sg_to_link_tbl_offset(struct scatterlist *sg, int sg_count,
				 unsigned int offset, int datalen, int elen,
				 struct talitos_ptr *link_tbl_ptr)
{
	int n_sg = elen ? sg_count + 1 : sg_count;
	int count = 0;
	int cryptlen = datalen + elen;

	while (cryptlen && sg && n_sg--) {
		unsigned int len = sg_dma_len(sg);

		if (offset >= len) {
			offset -= len;
			goto next;
		}

		len -= offset;

		if (len > cryptlen)
			len = cryptlen;

		if (datalen > 0 && len > datalen) {
			to_talitos_ptr(link_tbl_ptr + count,
				       sg_dma_address(sg) + offset, datalen, 0);
			to_talitos_ptr_ext_set(link_tbl_ptr + count, 0, 0);
			count++;
			len -= datalen;
			offset += datalen;
		}
		to_talitos_ptr(link_tbl_ptr + count,
			       sg_dma_address(sg) + offset, len, 0);
		to_talitos_ptr_ext_set(link_tbl_ptr + count, 0, 0);
		count++;
		cryptlen -= len;
		datalen -= len;
		offset = 0;

next:
		sg = sg_next(sg);
	}

	/* tag end of link table */
	if (count > 0)
		to_talitos_ptr_ext_set(link_tbl_ptr + count - 1,
				       DESC_PTR_LNKTBL_RET, 0);

	return count;
}