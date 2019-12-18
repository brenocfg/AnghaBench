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
struct TYPE_4__ {int fmt; int dch; int /*<<< orphan*/  channel; scalar_t__ run; } ;
struct TYPE_3__ {int fmt; int dch; int /*<<< orphan*/  channel; scalar_t__ run; } ;
struct sb_info {int bd_flags; TYPE_2__ rch; TYPE_1__ pch; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_8BIT ; 
 int BD_F_SB16X ; 
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  DSP_DATA_AVL16 ; 
 int /*<<< orphan*/  IRQ_STAT ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int sb_getmixer (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_lock (struct sb_info*) ; 
 int /*<<< orphan*/  sb_rd (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_unlock (struct sb_info*) ; 

__attribute__((used)) static void
sb_intr(void *arg)
{
    	struct sb_info *sb = (struct sb_info *)arg;
    	int reason, c;

    	/*
     	 * The Vibra16X has separate flags for 8 and 16 bit transfers, but
     	 * I have no idea how to tell capture from playback interrupts...
     	 */

	reason = 0;
	sb_lock(sb);
    	c = sb_getmixer(sb, IRQ_STAT);
    	if (c & 1)
		sb_rd(sb, DSP_DATA_AVAIL); /* 8-bit int ack */

    	if (c & 2)
		sb_rd(sb, DSP_DATA_AVL16); /* 16-bit int ack */
	sb_unlock(sb);

	/*
	 * this tells us if the source is 8-bit or 16-bit dma. We
     	 * have to check the io channel to map it to read or write...
     	 */

	if (sb->bd_flags & BD_F_SB16X) {
    		if (c & 1) { /* 8-bit format */
			if (sb->pch.fmt & AFMT_8BIT)
				reason |= 1;
			if (sb->rch.fmt & AFMT_8BIT)
				reason |= 2;
    		}
    		if (c & 2) { /* 16-bit format */
			if (sb->pch.fmt & AFMT_16BIT)
				reason |= 1;
			if (sb->rch.fmt & AFMT_16BIT)
				reason |= 2;
    		}
	} else {
    		if (c & 1) { /* 8-bit dma */
			if (sb->pch.dch == 1)
				reason |= 1;
			if (sb->rch.dch == 1)
				reason |= 2;
    		}
    		if (c & 2) { /* 16-bit dma */
			if (sb->pch.dch == 2)
				reason |= 1;
			if (sb->rch.dch == 2)
				reason |= 2;
    		}
	}
#if 0
    	printf("sb_intr: reason=%d c=0x%x\n", reason, c);
#endif
    	if ((reason & 1) && (sb->pch.run))
		chn_intr(sb->pch.channel);

    	if ((reason & 2) && (sb->rch.run))
		chn_intr(sb->rch.channel);
}