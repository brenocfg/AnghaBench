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
struct zatm_vcc {int rx_chan; } ;
struct zatm_dev {int /*<<< orphan*/  lock; } ;
struct atm_vcc {int vci; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 struct zatm_dev* ZATM_DEV (int /*<<< orphan*/ ) ; 
 struct zatm_vcc* ZATM_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  inb_p (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int uPD98401_RXLT_ENBL ; 
 int zpeekl (struct zatm_dev*,int) ; 
 int /*<<< orphan*/  zpokel (struct zatm_dev*,int,int) ; 

__attribute__((used)) static int open_rx_second(struct atm_vcc *vcc)
{
	struct zatm_dev *zatm_dev;
	struct zatm_vcc *zatm_vcc;
	unsigned long flags;
	int pos,shift;

	DPRINTK("open_rx_second (0x%x)\n",inb_p(0xc053));
	zatm_dev = ZATM_DEV(vcc->dev);
	zatm_vcc = ZATM_VCC(vcc);
	if (!zatm_vcc->rx_chan) return 0;
	spin_lock_irqsave(&zatm_dev->lock, flags);
	/* should also handle VPI @@@ */
	pos = vcc->vci >> 1;
	shift = (1-(vcc->vci & 1)) << 4;
	zpokel(zatm_dev,(zpeekl(zatm_dev,pos) & ~(0xffff << shift)) |
	    ((zatm_vcc->rx_chan | uPD98401_RXLT_ENBL) << shift),pos);
	spin_unlock_irqrestore(&zatm_dev->lock, flags);
	return 0;
}