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
struct mmp_tdma_desc {int dummy; } ;
struct mmp_tdma_chan {int desc_num; int /*<<< orphan*/ * desc_arr; struct gen_pool* pool; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (struct gen_pool*,unsigned long,int) ; 

__attribute__((used)) static void mmp_tdma_free_descriptor(struct mmp_tdma_chan *tdmac)
{
	struct gen_pool *gpool;
	int size = tdmac->desc_num * sizeof(struct mmp_tdma_desc);

	gpool = tdmac->pool;
	if (gpool && tdmac->desc_arr)
		gen_pool_free(gpool, (unsigned long)tdmac->desc_arr,
				size);
	tdmac->desc_arr = NULL;

	return;
}