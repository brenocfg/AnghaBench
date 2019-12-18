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
typedef  scalar_t__ u8 ;
struct sg_mapping_iter {unsigned int length; int consumed; scalar_t__* addr; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 unsigned int SG_MITER_FROM_SG ; 
 int /*<<< orphan*/  sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,struct scatterlist*,int,unsigned int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int sg_nents_for_len (struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int caam_rsa_count_leading_zeros(struct scatterlist *sgl,
					unsigned int nbytes,
					unsigned int flags)
{
	struct sg_mapping_iter miter;
	int lzeros, ents;
	unsigned int len;
	unsigned int tbytes = nbytes;
	const u8 *buff;

	ents = sg_nents_for_len(sgl, nbytes);
	if (ents < 0)
		return ents;

	sg_miter_start(&miter, sgl, ents, SG_MITER_FROM_SG | flags);

	lzeros = 0;
	len = 0;
	while (nbytes > 0) {
		/* do not strip more than given bytes */
		while (len && !*buff && lzeros < nbytes) {
			lzeros++;
			len--;
			buff++;
		}

		if (len && *buff)
			break;

		sg_miter_next(&miter);
		buff = miter.addr;
		len = miter.length;

		nbytes -= lzeros;
		lzeros = 0;
	}

	miter.consumed = lzeros;
	sg_miter_stop(&miter);
	nbytes -= lzeros;

	return tbytes - nbytes;
}