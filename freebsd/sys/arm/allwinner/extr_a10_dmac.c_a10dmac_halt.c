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
typedef  int /*<<< orphan*/  uint32_t ;
struct a10dmac_channel {scalar_t__ ch_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWIN_DDMA_CTL_DMA_LOADING ; 
 int /*<<< orphan*/  AWIN_NDMA_CTL_DMA_LOADING ; 
 scalar_t__ CH_NDMA ; 
 int /*<<< orphan*/  a10dmac_read_ctl (struct a10dmac_channel*) ; 
 int /*<<< orphan*/  a10dmac_write_ctl (struct a10dmac_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a10dmac_halt(device_t dev, void *priv)
{
	struct a10dmac_channel *ch = priv;
	uint32_t cfg;

	cfg = a10dmac_read_ctl(ch);
	if (ch->ch_type == CH_NDMA) {
		cfg &= ~AWIN_NDMA_CTL_DMA_LOADING;
	} else {
		cfg &= ~AWIN_DDMA_CTL_DMA_LOADING;
	}
	a10dmac_write_ctl(ch, cfg);
}