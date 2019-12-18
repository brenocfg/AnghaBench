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
struct sc_info {int dummy; } ;
struct sc_chinfo {int format; int dma_active; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int /*<<< orphan*/  ALS_FIFO1_CONTROL ; 
 int /*<<< orphan*/  ALS_FIFO1_LENGTH_HI ; 
 int /*<<< orphan*/  ALS_FIFO1_LENGTH_LO ; 
 int ALS_FIFO1_RUN ; 
 int /*<<< orphan*/  ALS_GCR_FIFO1_COUNT ; 
 int /*<<< orphan*/  ALS_GCR_FIFO1_START ; 
 int /*<<< orphan*/  DSP_CMD_SPKON ; 
 int /*<<< orphan*/  als_esp_wr (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  als_gcr_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int als_get_fifo_format (struct sc_info*,int) ; 
 int /*<<< orphan*/  als_mix_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  als_set_speed (struct sc_chinfo*) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
als_capture_start(struct sc_chinfo *ch)
{
	struct	sc_info *sc = ch->parent;
	u_int32_t	buf, bufsz, count, dma_prog;

	buf = sndbuf_getbufaddr(ch->buffer);
	bufsz = sndbuf_getsize(ch->buffer);
	count = bufsz / 2;
	if (ch->format & AFMT_16BIT)
		count /= 2;
	count--;

	als_esp_wr(sc, DSP_CMD_SPKON);
	als_set_speed(ch);

	als_gcr_wr(sc, ALS_GCR_FIFO1_START, buf);
	als_gcr_wr(sc, ALS_GCR_FIFO1_COUNT, (bufsz - 1));

	als_mix_wr(sc, ALS_FIFO1_LENGTH_LO, count & 0xff);
	als_mix_wr(sc, ALS_FIFO1_LENGTH_HI, count >> 8);

	dma_prog = ALS_FIFO1_RUN | als_get_fifo_format(sc, ch->format);
	als_mix_wr(sc, ALS_FIFO1_CONTROL, dma_prog);

	ch->dma_active = 1;
}