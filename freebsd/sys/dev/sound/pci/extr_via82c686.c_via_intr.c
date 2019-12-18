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
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct via_info {int /*<<< orphan*/  lock; TYPE_1__ rch; TYPE_2__ pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIA_PLAY_STAT ; 
 int /*<<< orphan*/  VIA_RECORD_STAT ; 
 int VIA_RPSTAT_INTR ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int via_rd (struct via_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
via_intr(void *p)
{
	struct via_info *via = p;

	/* DEB(printf("viachan_intr\n")); */
	/* Read channel */
	snd_mtxlock(via->lock);
	if (via_rd(via, VIA_PLAY_STAT, 1) & VIA_RPSTAT_INTR) {
		via_wr(via, VIA_PLAY_STAT, VIA_RPSTAT_INTR, 1);
		snd_mtxunlock(via->lock);
		chn_intr(via->pch.channel);
		snd_mtxlock(via->lock);
	}

	/* Write channel */
	if (via_rd(via, VIA_RECORD_STAT, 1) & VIA_RPSTAT_INTR) {
		via_wr(via, VIA_RECORD_STAT, VIA_RPSTAT_INTR, 1);
		snd_mtxunlock(via->lock);
		chn_intr(via->rch.channel);
		return;
	}
	snd_mtxunlock(via->lock);
}