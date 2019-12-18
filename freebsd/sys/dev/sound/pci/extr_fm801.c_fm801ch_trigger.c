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
typedef  int u_int32_t ;
struct fm801_info {int play_start; int play_nextblk; int play_blksize; int play_fmt; int play_shift; int rec_start; int rec_nextblk; int rec_blksize; int rec_fmt; int rec_shift; scalar_t__ rec_flip; scalar_t__ play_flip; } ;
struct fm801_chinfo {scalar_t__ dir; int /*<<< orphan*/  buffer; struct fm801_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 int FM_PLAY_BUF1_LAST ; 
 int FM_PLAY_BUF2_LAST ; 
 int /*<<< orphan*/  FM_PLAY_CTL ; 
 int /*<<< orphan*/  FM_PLAY_DMABUF1 ; 
 int /*<<< orphan*/  FM_PLAY_DMABUF2 ; 
 int /*<<< orphan*/  FM_PLAY_DMALEN ; 
 int FM_PLAY_START ; 
 int FM_PLAY_STOPNOW ; 
 int FM_REC_BUF1_LAST ; 
 int FM_REC_BUF2_LAST ; 
 int /*<<< orphan*/  FM_REC_CTL ; 
 int /*<<< orphan*/  FM_REC_DMABUF1 ; 
 int /*<<< orphan*/  FM_REC_DMABUF2 ; 
 int /*<<< orphan*/  FM_REC_DMALEN ; 
 int FM_REC_START ; 
 int FM_REC_STOPNOW ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ PCMDIR_REC ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int fm801_rd (struct fm801_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm801_wr (struct fm801_info*,int /*<<< orphan*/ ,int,int) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fm801ch_trigger(kobj_t obj, void *data, int go)
{
	struct fm801_chinfo *ch = data;
	struct fm801_info *fm801 = ch->parent;
	u_int32_t baseaddr = sndbuf_getbufaddr(ch->buffer);
	u_int32_t k1;

	DPRINT("fm801ch_trigger go %d , ", go);

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (ch->dir == PCMDIR_PLAY) {
		if (go == PCMTRIG_START) {

			fm801->play_start = baseaddr;
			fm801->play_nextblk = fm801->play_start + fm801->play_blksize;
			fm801->play_flip = 0;
			fm801_wr(fm801, FM_PLAY_DMALEN, fm801->play_blksize - 1, 2);
			fm801_wr(fm801, FM_PLAY_DMABUF1,fm801->play_start,4);
			fm801_wr(fm801, FM_PLAY_DMABUF2,fm801->play_nextblk,4);
			fm801_wr(fm801, FM_PLAY_CTL,
					FM_PLAY_START | FM_PLAY_STOPNOW | fm801->play_fmt | fm801->play_shift,
					2 );
			} else {
			fm801->play_flip = 0;
			k1 = fm801_rd(fm801, FM_PLAY_CTL,2);
			fm801_wr(fm801, FM_PLAY_CTL,
				(k1 & ~(FM_PLAY_STOPNOW | FM_PLAY_START)) |
				FM_PLAY_BUF1_LAST | FM_PLAY_BUF2_LAST, 2 );
		}
	} else if(ch->dir == PCMDIR_REC) {
		if (go == PCMTRIG_START) {
			fm801->rec_start = baseaddr;
			fm801->rec_nextblk = fm801->rec_start + fm801->rec_blksize;
			fm801->rec_flip = 0;
			fm801_wr(fm801, FM_REC_DMALEN, fm801->rec_blksize - 1, 2);
			fm801_wr(fm801, FM_REC_DMABUF1,fm801->rec_start,4);
			fm801_wr(fm801, FM_REC_DMABUF2,fm801->rec_nextblk,4);
			fm801_wr(fm801, FM_REC_CTL,
					FM_REC_START | FM_REC_STOPNOW | fm801->rec_fmt | fm801->rec_shift,
					2 );
			} else {
			fm801->rec_flip = 0;
			k1 = fm801_rd(fm801, FM_REC_CTL,2);
			fm801_wr(fm801, FM_REC_CTL,
				(k1 & ~(FM_REC_STOPNOW | FM_REC_START)) |
				FM_REC_BUF1_LAST | FM_REC_BUF2_LAST, 2);
		}
	}

	return 0;
}