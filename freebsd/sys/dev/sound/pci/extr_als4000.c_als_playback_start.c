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
struct playback_command {int dma_prog; int format_val; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int /*<<< orphan*/  ALS_GCR_DMA0_MODE ; 
 int /*<<< orphan*/  ALS_GCR_DMA0_START ; 
 int DSP_CMD_SPKON ; 
 int DSP_F16_AUTO ; 
 int DSP_F16_DAC ; 
 int DSP_F16_FIFO_ON ; 
 int /*<<< orphan*/  als_esp_wr (struct sc_info*,int) ; 
 int /*<<< orphan*/  als_gcr_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 struct playback_command* als_get_playback_command (int) ; 
 int /*<<< orphan*/  als_set_speed (struct sc_chinfo*) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
als_playback_start(struct sc_chinfo *ch)
{
	const struct playback_command *p;
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

	als_gcr_wr(sc, ALS_GCR_DMA0_START, buf);
	als_gcr_wr(sc, ALS_GCR_DMA0_MODE, (bufsz - 1) | 0x180000);

	p = als_get_playback_command(ch->format);
	dma_prog = p->dma_prog | DSP_F16_DAC | DSP_F16_AUTO | DSP_F16_FIFO_ON;

	als_esp_wr(sc, dma_prog);
	als_esp_wr(sc, p->format_val);
	als_esp_wr(sc, count & 0xff);
	als_esp_wr(sc, count >> 8);

	ch->dma_active = 1;
}