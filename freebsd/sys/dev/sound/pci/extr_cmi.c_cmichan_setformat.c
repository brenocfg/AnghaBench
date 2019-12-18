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
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {int bps; scalar_t__ dir; int fmt; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S16_LE ; 
 int /*<<< orphan*/  CMPCI_REG_CH0_FORMAT_MASK ; 
 int /*<<< orphan*/  CMPCI_REG_CH0_FORMAT_SHIFT ; 
 int /*<<< orphan*/  CMPCI_REG_CH1_FORMAT_MASK ; 
 int /*<<< orphan*/  CMPCI_REG_CH1_FORMAT_SHIFT ; 
 int /*<<< orphan*/  CMPCI_REG_CHANNEL_FORMAT ; 
 int CMPCI_REG_FORMAT_16BIT ; 
 int CMPCI_REG_FORMAT_8BIT ; 
 int CMPCI_REG_FORMAT_MONO ; 
 int CMPCI_REG_FORMAT_STEREO ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  cmi_partial_wr4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmichan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct sc_chinfo *ch = data;
	struct sc_info	*sc = ch->parent;
	u_int32_t f;

	if (format & AFMT_S16_LE) {
		f = CMPCI_REG_FORMAT_16BIT;
		ch->bps = 2;
	} else {
		f = CMPCI_REG_FORMAT_8BIT;
		ch->bps = 1;
	}

	if (AFMT_CHANNEL(format) > 1) {
		f |= CMPCI_REG_FORMAT_STEREO;
		ch->bps *= 2;
	} else {
		f |= CMPCI_REG_FORMAT_MONO;
	}

	snd_mtxlock(sc->lock);
	if (ch->dir == PCMDIR_PLAY) {
		cmi_partial_wr4(ch->parent,
				CMPCI_REG_CHANNEL_FORMAT,
				CMPCI_REG_CH0_FORMAT_SHIFT,
				CMPCI_REG_CH0_FORMAT_MASK,
				f);
	} else {
		cmi_partial_wr4(ch->parent,
				CMPCI_REG_CHANNEL_FORMAT,
				CMPCI_REG_CH1_FORMAT_SHIFT,
				CMPCI_REG_CH1_FORMAT_MASK,
				f);
	}
	snd_mtxunlock(sc->lock);
	ch->fmt = format;

	return 0;
}