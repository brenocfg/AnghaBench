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
struct mss_info {int io_rid; int conf_rid; int drq1_rid; int drq2_rid; int /*<<< orphan*/ * conf_base; int /*<<< orphan*/  bd_id; scalar_t__ irq_rid; int /*<<< orphan*/  bd_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BD_F_MSS_OFFSET ; 
 int DV_F_DRQ_MASK ; 
 int DV_F_DUAL_DMA ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MD_GUSMAX ; 
 int /*<<< orphan*/  MD_GUSPNP ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int isa_get_drq (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int mss_doattach (int /*<<< orphan*/ ,struct mss_info*) ; 
 int /*<<< orphan*/  mss_release_resources (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ *,int,unsigned char) ; 

__attribute__((used)) static int
guspcm_attach(device_t dev)
{
	device_t parent = device_get_parent(dev);
	struct mss_info *mss;
	int base, flags;
	unsigned char ctl;

	mss = (struct mss_info *)malloc(sizeof *mss, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mss == NULL)
		return ENOMEM;

	mss->bd_flags = BD_F_MSS_OFFSET;
	mss->io_rid = 2;
	mss->conf_rid = 1;
	mss->irq_rid = 0;
	mss->drq1_rid = 1;
	mss->drq2_rid = -1;

	if (isa_get_logicalid(parent) == 0)
		mss->bd_id = MD_GUSMAX;
	else {
		mss->bd_id = MD_GUSPNP;
		mss->drq2_rid = 0;
		goto skip_setup;
	}

	flags = device_get_flags(parent);
	if (flags & DV_F_DUAL_DMA)
		mss->drq2_rid = 0;

	mss->conf_base = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
						     &mss->conf_rid,
						     8, RF_ACTIVE);

	if (mss->conf_base == NULL) {
		mss_release_resources(mss, dev);
		return ENXIO;
	}

	base = isa_get_port(parent);

	ctl = 0x40;			/* CS4231 enable */
	if (isa_get_drq(dev) > 3)
		ctl |= 0x10;		/* 16-bit dma channel 1 */
	if ((flags & DV_F_DUAL_DMA) != 0 && (flags & DV_F_DRQ_MASK) > 3)
		ctl |= 0x20;		/* 16-bit dma channel 2 */
	ctl |= (base >> 4) & 0x0f;	/* 2X0 -> 3XC */
	port_wr(mss->conf_base, 6, ctl);

skip_setup:
	return mss_doattach(dev, mss);
}