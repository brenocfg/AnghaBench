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
struct sc_chinfo {int lvol; int rvol; int /*<<< orphan*/  rslot; int /*<<< orphan*/  lslot; } ;

/* Variables and functions */
 int HDSPE_MAX_GAIN ; 
 int /*<<< orphan*/  hdspe_hw_mixer (struct sc_chinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hdspechan_setgain(struct sc_chinfo *ch)
{

	hdspe_hw_mixer(ch, ch->lslot, ch->lslot,
	    ch->lvol * HDSPE_MAX_GAIN / 100);
	hdspe_hw_mixer(ch, ch->rslot, ch->rslot,
	    ch->rvol * HDSPE_MAX_GAIN / 100);

	return (0);
}