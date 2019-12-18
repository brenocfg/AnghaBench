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
struct tr_chinfo {int fmc; int eso; int rvol; int cvol; int active; scalar_t__ bufhalf; scalar_t__ vol; scalar_t__ pan; scalar_t__ gvsel; int /*<<< orphan*/  buffer; scalar_t__ cso; int /*<<< orphan*/  lba; scalar_t__ alpha; scalar_t__ ec; scalar_t__ fms; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int sndbuf_getalign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_enaint (struct tr_chinfo*,int) ; 
 int /*<<< orphan*/  tr_startch (struct tr_chinfo*) ; 
 int /*<<< orphan*/  tr_stopch (struct tr_chinfo*) ; 
 int /*<<< orphan*/  tr_wrch (struct tr_chinfo*) ; 

__attribute__((used)) static int
trpchan_trigger(kobj_t obj, void *data, int go)
{
	struct tr_chinfo *ch = data;

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (go == PCMTRIG_START) {
		ch->fmc = 3;
		ch->fms = 0;
		ch->ec = 0;
		ch->alpha = 0;
		ch->lba = sndbuf_getbufaddr(ch->buffer);
		ch->cso = 0;
		ch->eso = (sndbuf_getsize(ch->buffer) / sndbuf_getalign(ch->buffer)) - 1;
		ch->rvol = ch->cvol = 0x7f;
		ch->gvsel = 0;
		ch->pan = 0;
		ch->vol = 0;
		ch->bufhalf = 0;
   		tr_wrch(ch);
		tr_enaint(ch, 1);
		tr_startch(ch);
		ch->active = 1;
	} else {
		tr_stopch(ch);
		ch->active = 0;
	}

	return 0;
}