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
struct nbpf_channel {int dmarq_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBPF_CHAN_CFG ; 
 int NBPF_CHAN_CFG_DMS ; 
 int /*<<< orphan*/  nbpf_chan_write (struct nbpf_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nbpf_chan_configure(struct nbpf_channel *chan)
{
	/*
	 * We assume, that only the link mode and DMA request line configuration
	 * have to be set in the configuration register manually. Dynamic
	 * per-transfer configuration will be loaded from transfer descriptors.
	 */
	nbpf_chan_write(chan, NBPF_CHAN_CFG, NBPF_CHAN_CFG_DMS | chan->dmarq_cfg);
}