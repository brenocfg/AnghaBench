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
typedef  int uint32_t ;
struct es_info {int ctrl; int sctrl; scalar_t__ polling; int poll_ticks; int /*<<< orphan*/  poll_timer; } ;
struct es_chinfo {int blksz; int fmt; scalar_t__ dir; scalar_t__ index; int bufsz; int active; scalar_t__ prevptr; scalar_t__ ptr; int /*<<< orphan*/  buffer; struct es_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 
 int CTRL_ADC_EN ; 
 int CTRL_DAC1_EN ; 
 int CTRL_DAC2_EN ; 
 int ES1370_REG_ADC_FRAMECNT ; 
 int ES1370_REG_ADC_SCOUNT ; 
 int ES1370_REG_CONTROL ; 
 int ES1370_REG_DAC1_FRAMECNT ; 
 int ES1370_REG_DAC1_SCOUNT ; 
 int ES1370_REG_DAC2_FRAMECNT ; 
 int ES1370_REG_DAC2_SCOUNT ; 
 int ES1370_REG_MEMPAGE ; 
 int ES1370_REG_SERIAL_CONTROL ; 
 scalar_t__ ES_DAC1 ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int SCTRL_P1INTEN ; 
 int SCTRL_P1LOOPSEL ; 
 int SCTRL_P1PAUSE ; 
 int SCTRL_P1SCTRLD ; 
 int SCTRL_P2DACSEN ; 
 int SCTRL_P2ENDINC ; 
 int SCTRL_P2INTEN ; 
 int SCTRL_P2LOOPSEL ; 
 int SCTRL_P2PAUSE ; 
 int SCTRL_P2STINC ; 
 int SCTRL_R1INTEN ; 
 int SCTRL_R1LOOPSEL ; 
 int SCTRL_SH_P2ENDINC ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct es_info*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ es_chan_active (struct es_info*) ; 
 int /*<<< orphan*/  es_poll_callback ; 
 int /*<<< orphan*/  es_wr (struct es_info*,int,int,int) ; 
 int sndbuf_getalign (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eschan_trigger(kobj_t obj, void *data, int go)
{
	struct es_chinfo *ch = data;
	struct es_info *es = ch->parent;
	uint32_t cnt, b = 0;

	if (!PCMTRIG_COMMON(go))
		return 0;

	ES_LOCK(es);
	cnt = (ch->blksz / sndbuf_getalign(ch->buffer)) - 1;
	if (ch->fmt & AFMT_16BIT)
		b |= 0x02;
	if (AFMT_CHANNEL(ch->fmt) > 1)
		b |= 0x01;
	if (ch->dir == PCMDIR_PLAY) {
		if (go == PCMTRIG_START) {
			if (ch->index == ES_DAC1) {
				es->ctrl |= CTRL_DAC1_EN;
				es->sctrl &= ~(SCTRL_P1LOOPSEL |
				    SCTRL_P1PAUSE | SCTRL_P1SCTRLD);
				if (es->polling == 0)
					es->sctrl |= SCTRL_P1INTEN;
				else
					es->sctrl &= ~SCTRL_P1INTEN;
				es->sctrl |= b;
				es_wr(es, ES1370_REG_DAC1_SCOUNT, cnt, 4);
				/* start at beginning of buffer */
				es_wr(es, ES1370_REG_MEMPAGE,
				    ES1370_REG_DAC1_FRAMECNT >> 8, 4);
				es_wr(es, ES1370_REG_DAC1_FRAMECNT & 0xff,
				    (ch->bufsz >> 2) - 1, 4);
			} else {
				es->ctrl |= CTRL_DAC2_EN;
				es->sctrl &= ~(SCTRL_P2ENDINC | SCTRL_P2STINC |
				    SCTRL_P2LOOPSEL | SCTRL_P2PAUSE |
				    SCTRL_P2DACSEN);
				if (es->polling == 0)
					es->sctrl |= SCTRL_P2INTEN;
				else
					es->sctrl &= ~SCTRL_P2INTEN;
				es->sctrl |= (b << 2) |
				    ((((b >> 1) & 1) + 1) << SCTRL_SH_P2ENDINC);
				es_wr(es, ES1370_REG_DAC2_SCOUNT, cnt, 4);
				/* start at beginning of buffer */
				es_wr(es, ES1370_REG_MEMPAGE,
				    ES1370_REG_DAC2_FRAMECNT >> 8, 4);
				es_wr(es, ES1370_REG_DAC2_FRAMECNT & 0xff,
				    (ch->bufsz >> 2) - 1, 4);
			}
		} else
			es->ctrl &= ~((ch->index == ES_DAC1) ?
			    CTRL_DAC1_EN : CTRL_DAC2_EN);
	} else {
		if (go == PCMTRIG_START) {
			es->ctrl |= CTRL_ADC_EN;
			es->sctrl &= ~SCTRL_R1LOOPSEL;
			if (es->polling == 0)
				es->sctrl |= SCTRL_R1INTEN;
			else
				es->sctrl &= ~SCTRL_R1INTEN;
			es->sctrl |= b << 4;
			es_wr(es, ES1370_REG_ADC_SCOUNT, cnt, 4);
			/* start at beginning of buffer */
			es_wr(es, ES1370_REG_MEMPAGE,
			    ES1370_REG_ADC_FRAMECNT >> 8, 4);
			es_wr(es, ES1370_REG_ADC_FRAMECNT & 0xff,
			    (ch->bufsz >> 2) - 1, 4);
		} else
			es->ctrl &= ~CTRL_ADC_EN;
	}
	es_wr(es, ES1370_REG_SERIAL_CONTROL, es->sctrl, 4);
	es_wr(es, ES1370_REG_CONTROL, es->ctrl, 4);
	if (go == PCMTRIG_START) {
		if (es->polling != 0) {
			ch->ptr = 0;
			ch->prevptr = 0;
			if (es_chan_active(es) == 0) {
				es->poll_ticks = 1;
				callout_reset(&es->poll_timer, 1,
				    es_poll_callback, es);
			}
		}
		ch->active = 1;
	} else {
		ch->active = 0;
		if (es->polling != 0) {
			if (es_chan_active(es) == 0) {
				callout_stop(&es->poll_timer);
				es->poll_ticks = 1;
			}
		}
	}
	ES_UNLOCK(es);
	return (0);
}