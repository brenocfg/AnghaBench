#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct atmel_tdes_dev {TYPE_2__ dma_lch_out; TYPE_1__ dma_lch_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_tdes_dma_cleanup(struct atmel_tdes_dev *dd)
{
	dma_release_channel(dd->dma_lch_in.chan);
	dma_release_channel(dd->dma_lch_out.chan);
}