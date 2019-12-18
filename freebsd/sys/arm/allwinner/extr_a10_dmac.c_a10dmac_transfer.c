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
typedef  int uint32_t ;
struct a10dmac_channel {scalar_t__ ch_type; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  size_t bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWIN_DDMA_BC_REG ; 
 int AWIN_DDMA_CTL_DMA_LOADING ; 
 int /*<<< orphan*/  AWIN_DDMA_DEST_START_ADDR_REG ; 
 int /*<<< orphan*/  AWIN_DDMA_SRC_START_ADDR_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_BC_REG ; 
 int AWIN_NDMA_CTL_DMA_LOADING ; 
 int /*<<< orphan*/  AWIN_NDMA_DEST_ADDR_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_SRC_ADDR_REG ; 
 scalar_t__ CH_NDMA ; 
 int /*<<< orphan*/  DMACH_WRITE (struct a10dmac_channel*,int /*<<< orphan*/ ,size_t) ; 
 int EBUSY ; 
 int a10dmac_read_ctl (struct a10dmac_channel*) ; 
 int /*<<< orphan*/  a10dmac_write_ctl (struct a10dmac_channel*,int) ; 

__attribute__((used)) static int
a10dmac_transfer(device_t dev, void *priv, bus_addr_t src, bus_addr_t dst,
    size_t nbytes)
{
	struct a10dmac_channel *ch = priv;
	uint32_t cfg;

	cfg = a10dmac_read_ctl(ch);
	if (ch->ch_type == CH_NDMA) {
		if (cfg & AWIN_NDMA_CTL_DMA_LOADING)
			return (EBUSY);

		DMACH_WRITE(ch, AWIN_NDMA_SRC_ADDR_REG, src);
		DMACH_WRITE(ch, AWIN_NDMA_DEST_ADDR_REG, dst);
		DMACH_WRITE(ch, AWIN_NDMA_BC_REG, nbytes);

		cfg |= AWIN_NDMA_CTL_DMA_LOADING;
		a10dmac_write_ctl(ch, cfg);
	} else {
		if (cfg & AWIN_DDMA_CTL_DMA_LOADING)
			return (EBUSY);

		DMACH_WRITE(ch, AWIN_DDMA_SRC_START_ADDR_REG, src);
		DMACH_WRITE(ch, AWIN_DDMA_DEST_START_ADDR_REG, dst);
		DMACH_WRITE(ch, AWIN_DDMA_BC_REG, nbytes);

		cfg |= AWIN_DDMA_CTL_DMA_LOADING;
		a10dmac_write_ctl(ch, cfg);
	}

	return (0);
}