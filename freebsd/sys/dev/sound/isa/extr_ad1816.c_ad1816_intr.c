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
struct TYPE_4__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct ad1816_info {TYPE_2__ pch; TYPE_1__ rch; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816_INT ; 
 unsigned char AD1816_INTRCI ; 
 unsigned char AD1816_INTRPI ; 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 unsigned char io_rd (struct ad1816_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wr (struct ad1816_info*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  printf (char*,unsigned char) ; 
 scalar_t__ sndbuf_runsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ad1816_intr(void *arg)
{
    	struct ad1816_info *ad1816 = (struct ad1816_info *)arg;
    	unsigned char   c, served = 0;

	ad1816_lock(ad1816);
    	/* get interrupt status */
    	c = io_rd(ad1816, AD1816_INT);

    	/* check for stray interrupts */
    	if (c & ~(AD1816_INTRCI | AD1816_INTRPI)) {
		printf("pcm: stray int (%x)\n", c);
		c &= AD1816_INTRCI | AD1816_INTRPI;
    	}
    	/* check for capture interrupt */
    	if (sndbuf_runsz(ad1816->rch.buffer) && (c & AD1816_INTRCI)) {
		ad1816_unlock(ad1816);
		chn_intr(ad1816->rch.channel);
		ad1816_lock(ad1816);
		served |= AD1816_INTRCI;		/* cp served */
    	}
    	/* check for playback interrupt */
    	if (sndbuf_runsz(ad1816->pch.buffer) && (c & AD1816_INTRPI)) {
		ad1816_unlock(ad1816);
		chn_intr(ad1816->pch.channel);
		ad1816_lock(ad1816);
		served |= AD1816_INTRPI;		/* pb served */
    	}
    	if (served == 0) {
		/* this probably means this is not a (working) ad1816 chip, */
		/* or an error in dma handling                              */
		printf("pcm: int without reason (%x)\n", c);
		c = 0;
    	} else c &= ~served;
    	io_wr(ad1816, AD1816_INT, c);
    	c = io_rd(ad1816, AD1816_INT);
    	if (c != 0) printf("pcm: int clear failed (%x)\n", c);
	ad1816_unlock(ad1816);
}