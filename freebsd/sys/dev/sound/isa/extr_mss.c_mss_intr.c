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
typedef  int u_char ;
struct TYPE_4__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct mss_info {TYPE_2__ rch; TYPE_1__ pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BVDDB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 scalar_t__ FULL_DUPLEX (struct mss_info*) ; 
 int /*<<< orphan*/  MSS_STATUS ; 
 int ad_read (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int io_rd (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wr (struct mss_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sndbuf_runsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mss_intr(void *arg)
{
    	struct mss_info *mss = arg;
    	u_char c = 0, served = 0;
    	int i;

    	DEB(printf("mss_intr\n"));
	mss_lock(mss);
    	ad_read(mss, 11); /* fake read of status bits */

    	/* loop until there are interrupts, but no more than 10 times. */
    	for (i = 10; i > 0 && io_rd(mss, MSS_STATUS) & 1; i--) {
		/* get exact reason for full-duplex boards */
		c = FULL_DUPLEX(mss)? ad_read(mss, 24) : 0x30;
		c &= ~served;
		if (sndbuf_runsz(mss->pch.buffer) && (c & 0x10)) {
	    		served |= 0x10;
			mss_unlock(mss);
	    		chn_intr(mss->pch.channel);
			mss_lock(mss);
		}
		if (sndbuf_runsz(mss->rch.buffer) && (c & 0x20)) {
	    		served |= 0x20;
			mss_unlock(mss);
	    		chn_intr(mss->rch.channel);
			mss_lock(mss);
		}
		/* now ack the interrupt */
		if (FULL_DUPLEX(mss)) ad_write(mss, 24, ~c); /* ack selectively */
		else io_wr(mss, MSS_STATUS, 0);	/* Clear interrupt status */
    	}
    	if (i == 10) {
		BVDDB(printf("mss_intr: irq, but not from mss\n"));
	} else if (served == 0) {
		BVDDB(printf("mss_intr: unexpected irq with reason %x\n", c));
		/*
	 	* this should not happen... I have no idea what to do now.
	 	* maybe should do a sanity check and restart dmas ?
	 	*/
		io_wr(mss, MSS_STATUS, 0);	/* Clear interrupt status */
    	}
	mss_unlock(mss);
}