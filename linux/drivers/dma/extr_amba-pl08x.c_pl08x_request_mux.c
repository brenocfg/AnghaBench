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
struct pl08x_platform_data {int (* get_xfer_signal ) (int /*<<< orphan*/ ) ;} ;
struct pl08x_dma_chan {int signal; scalar_t__ mux_use; int /*<<< orphan*/  cd; TYPE_1__* host; } ;
struct TYPE_2__ {struct pl08x_platform_data* pd; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl08x_request_mux(struct pl08x_dma_chan *plchan)
{
	const struct pl08x_platform_data *pd = plchan->host->pd;
	int ret;

	if (plchan->mux_use++ == 0 && pd->get_xfer_signal) {
		ret = pd->get_xfer_signal(plchan->cd);
		if (ret < 0) {
			plchan->mux_use = 0;
			return ret;
		}

		plchan->signal = ret;
	}
	return 0;
}