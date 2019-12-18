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
typedef  int u_int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct sc_info {int /*<<< orphan*/  lock; TYPE_2__ rch; TYPE_1__ pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_CR1E_ACK_PORT ; 
 int /*<<< orphan*/  ALS_ESP_RD_STATUS16 ; 
 int /*<<< orphan*/  ALS_ESP_RD_STATUS8 ; 
 int ALS_IRQ_CR1E ; 
 int ALS_IRQ_MPUIN ; 
 int ALS_IRQ_STATUS16 ; 
 int ALS_IRQ_STATUS8 ; 
 int /*<<< orphan*/  ALS_MIDI_DATA ; 
 int /*<<< orphan*/  IRQ_STAT ; 
 int /*<<< orphan*/  als_ack_read (struct sc_info*,int /*<<< orphan*/ ) ; 
 int als_intr_rd (struct sc_info*) ; 
 int /*<<< orphan*/  als_intr_wr (struct sc_info*,int) ; 
 int als_mix_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
als_intr(void *p)
{
	struct sc_info *sc = (struct sc_info *)p;
	u_int8_t intr, sb_status;

	snd_mtxlock(sc->lock);
	intr = als_intr_rd(sc);

	if (intr & 0x80) {
		snd_mtxunlock(sc->lock);
		chn_intr(sc->pch.channel);
		snd_mtxlock(sc->lock);
	}

	if (intr & 0x40) {
		snd_mtxunlock(sc->lock);
		chn_intr(sc->rch.channel);
		snd_mtxlock(sc->lock);
	}

	/* ACK interrupt in PCI core */
	als_intr_wr(sc, intr);

	/* ACK interrupt in SB core */
	sb_status = als_mix_rd(sc, IRQ_STAT);

	if (sb_status & ALS_IRQ_STATUS8)
		als_ack_read(sc, ALS_ESP_RD_STATUS8);
	if (sb_status & ALS_IRQ_STATUS16)
		als_ack_read(sc, ALS_ESP_RD_STATUS16);
	if (sb_status & ALS_IRQ_MPUIN)
		als_ack_read(sc, ALS_MIDI_DATA);
	if (sb_status & ALS_IRQ_CR1E)
		als_ack_read(sc, ALS_CR1E_ACK_PORT);

	snd_mtxunlock(sc->lock);
	return;
}