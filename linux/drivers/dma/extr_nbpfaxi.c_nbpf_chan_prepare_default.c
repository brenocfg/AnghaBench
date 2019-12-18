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
struct nbpf_channel {int dmarq_cfg; scalar_t__ flags; scalar_t__ terminal; } ;

/* Variables and functions */
 int NBPF_CHAN_CFG_AM ; 

__attribute__((used)) static void nbpf_chan_prepare_default(struct nbpf_channel *chan)
{
	/* Don't output DMAACK */
	chan->dmarq_cfg = NBPF_CHAN_CFG_AM & 0x400;
	chan->terminal = 0;
	chan->flags = 0;
}