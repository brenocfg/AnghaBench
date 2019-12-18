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
struct omap_des_dev {int /*<<< orphan*/  dma_lch_out; int /*<<< orphan*/  dma_lch_in; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_des_dma_stop (struct omap_des_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_des_crypt_dma_stop(struct omap_des_dev *dd)
{
	pr_debug("total: %d\n", dd->total);

	omap_des_dma_stop(dd);

	dmaengine_terminate_all(dd->dma_lch_in);
	dmaengine_terminate_all(dd->dma_lch_out);

	return 0;
}