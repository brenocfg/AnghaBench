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
struct mss_info {int conf_rid; int drq2_rid; int bd_id; scalar_t__ drq1_rid; scalar_t__ irq_rid; scalar_t__ io_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DV_F_DEV_MASK ; 
 int DV_F_DEV_SHIFT ; 
 int DV_F_DRQ_MASK ; 
 int DV_F_DUAL_DMA ; 
 int ENXIO ; 
 int MD_YM0020 ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int mss_doattach (int /*<<< orphan*/ ,struct mss_info*) ; 
 int /*<<< orphan*/  ymf_test (int /*<<< orphan*/ ,struct mss_info*) ; 

__attribute__((used)) static int
mss_attach(device_t dev)
{
    	struct mss_info *mss;
    	int flags = device_get_flags(dev);

    	mss = (struct mss_info *)malloc(sizeof *mss, M_DEVBUF, M_NOWAIT | M_ZERO);
    	if (!mss) return ENXIO;

    	mss->io_rid = 0;
    	mss->conf_rid = -1;
    	mss->irq_rid = 0;
    	mss->drq1_rid = 0;
    	mss->drq2_rid = -1;
    	if (flags & DV_F_DUAL_DMA) {
        	bus_set_resource(dev, SYS_RES_DRQ, 1,
    		         	 flags & DV_F_DRQ_MASK, 1);
		mss->drq2_rid = 1;
    	}
    	mss->bd_id = (device_get_flags(dev) & DV_F_DEV_MASK) >> DV_F_DEV_SHIFT;
    	if (mss->bd_id == MD_YM0020) ymf_test(dev, mss);
    	return mss_doattach(dev, mss);
}