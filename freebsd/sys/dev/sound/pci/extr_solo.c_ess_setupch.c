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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct ess_info {int simplex_dir; scalar_t__ newspeed; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 
 int AFMT_SIGNED ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCMDIR_PLAY ; 
 int PCMDIR_REC ; 
 int ess_calcfilter (int) ; 
 int ess_calcspeed8 (int*) ; 
 int ess_calcspeed9 (int*) ; 
 int ess_read (struct ess_info*,int) ; 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  ess_write (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ess_setupch(struct ess_info *sc, int ch, int dir, int spd, u_int32_t fmt, int len)
{
	int play = (dir == PCMDIR_PLAY)? 1 : 0;
	int b16 = (fmt & AFMT_16BIT)? 1 : 0;
	int stereo = (AFMT_CHANNEL(fmt) > 1)? 1 : 0;
	int unsign = (!(fmt & AFMT_SIGNED))? 1 : 0;
	u_int8_t spdval, fmtval;

	DEB(printf("ess_setupch\n"));
	spdval = (sc->newspeed)? ess_calcspeed9(&spd) : ess_calcspeed8(&spd);

	sc->simplex_dir = play ? PCMDIR_PLAY : PCMDIR_REC ;

	if (ch == 1) {
		KASSERT((dir == PCMDIR_PLAY) || (dir == PCMDIR_REC), ("ess_setupch: dir1 bad"));
		len = -len;
		/* transfer length low */
		ess_write(sc, 0xa4, len & 0x00ff);
		/* transfer length high */
		ess_write(sc, 0xa5, (len & 0xff00) >> 8);
		/* autoinit, dma dir */
		ess_write(sc, 0xb8, 0x04 | (play? 0x00 : 0x0a));
		/* mono/stereo */
		ess_write(sc, 0xa8, (ess_read(sc, 0xa8) & ~0x03) | (stereo? 0x01 : 0x02));
		/* demand mode, 4 bytes/xfer */
		ess_write(sc, 0xb9, 0x02);
		/* sample rate */
        	ess_write(sc, 0xa1, spdval);
		/* filter cutoff */
		ess_write(sc, 0xa2, ess_calcfilter(spd));
		/* setup dac/adc */
		/*
		if (play)
			ess_write(sc, 0xb6, unsign? 0x80 : 0x00);
		*/
		/* mono, b16: signed, load signal */
		/*
		ess_write(sc, 0xb7, 0x51 | (unsign? 0x00 : 0x20));
		*/
		/* setup fifo */
		ess_write(sc, 0xb7, 0x91 | (unsign? 0x00 : 0x20) |
					   (b16? 0x04 : 0x00) |
					   (stereo? 0x08 : 0x40));
		/* irq control */
		ess_write(sc, 0xb1, (ess_read(sc, 0xb1) & 0x0f) | 0x50);
		/* drq control */
		ess_write(sc, 0xb2, (ess_read(sc, 0xb2) & 0x0f) | 0x50);
	} else if (ch == 2) {
		KASSERT(dir == PCMDIR_PLAY, ("ess_setupch: dir2 bad"));
		len >>= 1;
		len = -len;
		/* transfer length low */
		ess_setmixer(sc, 0x74, len & 0x00ff);
		/* transfer length high */
		ess_setmixer(sc, 0x76, (len & 0xff00) >> 8);
		/* autoinit, 4 bytes/req */
		ess_setmixer(sc, 0x78, 0x10);
		fmtval = b16 | (stereo << 1) | ((!unsign) << 2);
		/* enable irq, set format */
		ess_setmixer(sc, 0x7a, 0x40 | fmtval);
		if (sc->newspeed) {
			/* sample rate */
			ess_setmixer(sc, 0x70, spdval);
			/* filter cutoff */
			ess_setmixer(sc, 0x72, ess_calcfilter(spd));
		}

	}
	return 0;
}