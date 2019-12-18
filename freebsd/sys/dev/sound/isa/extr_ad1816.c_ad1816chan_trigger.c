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
struct ad1816_info {int dummy; } ;
struct ad1816_chinfo {scalar_t__ dir; int blksz; int /*<<< orphan*/  buffer; struct ad1816_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AD1816_CAPT ; 
 int AD1816_ENABLE ; 
 int AD1816_PLAY ; 
 scalar_t__ PCMDIR_PLAY ; 
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int ad1816_read (struct ad1816_info*,int) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_write (struct ad1816_info*,int,int) ; 
 int io_rd (struct ad1816_info*,int) ; 
 int /*<<< orphan*/  io_wr (struct ad1816_info*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sndbuf_dma (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ad1816chan_trigger(kobj_t obj, void *data, int go)
{
	struct ad1816_chinfo *ch = data;
    	struct ad1816_info *ad1816 = ch->parent;
    	int wr, reg;

	if (!PCMTRIG_COMMON(go))
		return 0;

	sndbuf_dma(ch->buffer, go);
    	wr = (ch->dir == PCMDIR_PLAY);
    	reg = wr? AD1816_PLAY : AD1816_CAPT;
	ad1816_lock(ad1816);
    	switch (go) {
    	case PCMTRIG_START:
		/* start only if not already running */
		if (!(io_rd(ad1816, reg) & AD1816_ENABLE)) {
	    		int cnt = ((ch->blksz) >> 2) - 1;
	    		ad1816_write(ad1816, wr? 8 : 10, cnt); /* count */
	    		ad1816_write(ad1816, wr? 9 : 11, 0); /* reset cur cnt */
	    		ad1816_write(ad1816, 1, ad1816_read(ad1816, 1) |
				     (wr? 0x8000 : 0x4000)); /* enable int */
	    		/* enable playback */
	    		io_wr(ad1816, reg, io_rd(ad1816, reg) | AD1816_ENABLE);
	    		if (!(io_rd(ad1816, reg) & AD1816_ENABLE))
				printf("ad1816: failed to start %s DMA!\n",
				       wr? "play" : "rec");
		}
		break;

    	case PCMTRIG_STOP:
    	case PCMTRIG_ABORT:		/* XXX check this... */
		/* we don't test here if it is running... */
		if (wr) {
	    		ad1816_write(ad1816, 1, ad1816_read(ad1816, 1) &
				     ~(wr? 0x8000 : 0x4000));
	    		/* disable int */
	    		io_wr(ad1816, reg, io_rd(ad1816, reg) & ~AD1816_ENABLE);
	    		/* disable playback */
	    		if (io_rd(ad1816, reg) & AD1816_ENABLE)
				printf("ad1816: failed to stop %s DMA!\n",
				       wr? "play" : "rec");
	    		ad1816_write(ad1816, wr? 8 : 10, 0); /* reset base cnt */
	    		ad1816_write(ad1816, wr? 9 : 11, 0); /* reset cur cnt */
		}
		break;
    	}
	ad1816_unlock(ad1816);
    	return 0;
}