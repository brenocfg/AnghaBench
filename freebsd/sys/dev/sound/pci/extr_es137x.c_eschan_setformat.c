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
struct es_info {int /*<<< orphan*/  sctrl; } ;
struct es_chinfo {scalar_t__ dir; scalar_t__ index; int fmt; struct es_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S16_LE ; 
 int /*<<< orphan*/  ES1370_REG_SERIAL_CONTROL ; 
 scalar_t__ ES_DAC1 ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  SCTRL_P1FMT ; 
 int /*<<< orphan*/  SCTRL_P1SEB ; 
 int /*<<< orphan*/  SCTRL_P1SMB ; 
 int /*<<< orphan*/  SCTRL_P2FMT ; 
 int /*<<< orphan*/  SCTRL_P2SEB ; 
 int /*<<< orphan*/  SCTRL_P2SMB ; 
 int /*<<< orphan*/  SCTRL_R1FMT ; 
 int /*<<< orphan*/  SCTRL_R1SEB ; 
 int /*<<< orphan*/  SCTRL_R1SMB ; 
 int /*<<< orphan*/  es_wr (struct es_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
eschan_setformat(kobj_t obj, void *data, uint32_t format)
{
	struct es_chinfo *ch = data;
	struct es_info *es = ch->parent;

	ES_LOCK(es);
	if (ch->dir == PCMDIR_PLAY) {
		if (ch->index == ES_DAC1) {
			es->sctrl &= ~SCTRL_P1FMT;
			if (format & AFMT_S16_LE)
				es->sctrl |= SCTRL_P1SEB;
			if (AFMT_CHANNEL(format) > 1)
				es->sctrl |= SCTRL_P1SMB;
		} else {
			es->sctrl &= ~SCTRL_P2FMT;
			if (format & AFMT_S16_LE)
				es->sctrl |= SCTRL_P2SEB;
			if (AFMT_CHANNEL(format) > 1)
				es->sctrl |= SCTRL_P2SMB;
		}
	} else {
		es->sctrl &= ~SCTRL_R1FMT;
		if (format & AFMT_S16_LE)
			es->sctrl |= SCTRL_R1SEB;
		if (AFMT_CHANNEL(format) > 1)
			es->sctrl |= SCTRL_R1SMB;
	}
	es_wr(es, ES1370_REG_SERIAL_CONTROL, es->sctrl, 4);
	ES_UNLOCK(es);
	ch->fmt = format;
	return (0);
}