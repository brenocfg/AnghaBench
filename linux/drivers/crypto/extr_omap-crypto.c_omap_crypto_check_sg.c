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
typedef  int u16 ;
struct scatterlist {int offset; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int OMAP_CRYPTO_BAD_DATA_LENGTH ; 
 int OMAP_CRYPTO_FORCE_SINGLE_ENTRY ; 
 int OMAP_CRYPTO_NOT_ALIGNED ; 
 scalar_t__ ZONE_DMA ; 
 scalar_t__ page_zonenum (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static int omap_crypto_check_sg(struct scatterlist *sg, int total, int bs,
				u16 flags)
{
	int len = 0;
	int num_sg = 0;

	if (!IS_ALIGNED(total, bs))
		return OMAP_CRYPTO_NOT_ALIGNED;

	while (sg) {
		num_sg++;

		if (!IS_ALIGNED(sg->offset, 4))
			return OMAP_CRYPTO_NOT_ALIGNED;
		if (!IS_ALIGNED(sg->length, bs))
			return OMAP_CRYPTO_NOT_ALIGNED;
#ifdef CONFIG_ZONE_DMA
		if (page_zonenum(sg_page(sg)) != ZONE_DMA)
			return OMAP_CRYPTO_NOT_ALIGNED;
#endif

		len += sg->length;
		sg = sg_next(sg);

		if (len >= total)
			break;
	}

	if ((flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY) && num_sg > 1)
		return OMAP_CRYPTO_NOT_ALIGNED;

	if (len != total)
		return OMAP_CRYPTO_BAD_DATA_LENGTH;

	return 0;
}