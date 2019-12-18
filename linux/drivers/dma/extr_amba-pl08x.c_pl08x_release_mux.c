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
struct pl08x_platform_data {int /*<<< orphan*/  (* put_xfer_signal ) (int /*<<< orphan*/ ,int) ;} ;
struct pl08x_dma_chan {int signal; scalar_t__ mux_use; int /*<<< orphan*/  cd; TYPE_1__* host; } ;
struct TYPE_2__ {struct pl08x_platform_data* pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pl08x_release_mux(struct pl08x_dma_chan *plchan)
{
	const struct pl08x_platform_data *pd = plchan->host->pd;

	if (plchan->signal >= 0) {
		WARN_ON(plchan->mux_use == 0);

		if (--plchan->mux_use == 0 && pd->put_xfer_signal) {
			pd->put_xfer_signal(plchan->cd, plchan->signal);
			plchan->signal = -1;
		}
	}
}