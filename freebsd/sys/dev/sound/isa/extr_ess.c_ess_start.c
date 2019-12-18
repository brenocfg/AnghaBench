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
struct ess_info {int dummy; } ;
struct ess_chinfo {int hwch; scalar_t__ stopping; int /*<<< orphan*/  blksz; int /*<<< orphan*/  fmt; int /*<<< orphan*/  spd; int /*<<< orphan*/  dir; struct ess_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_CMD_SPKON ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  ess_cmd (struct ess_info*,int /*<<< orphan*/ ) ; 
 int ess_getmixer (struct ess_info*,int) ; 
 int /*<<< orphan*/  ess_lock (struct ess_info*) ; 
 int ess_read (struct ess_info*,int) ; 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  ess_setupch (struct ess_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ess_unlock (struct ess_info*) ; 
 int /*<<< orphan*/  ess_write (struct ess_info*,int,int) ; 

__attribute__((used)) static int
ess_start(struct ess_chinfo *ch)
{
	struct ess_info *sc = ch->parent;
    	int play = (ch->dir == PCMDIR_PLAY)? 1 : 0;

	ess_lock(sc);
	ess_setupch(sc, ch->hwch, ch->dir, ch->spd, ch->fmt, ch->blksz);
	ch->stopping = 0;
	if (ch->hwch == 1)
		ess_write(sc, 0xb8, ess_read(sc, 0xb8) | 0x01);
	else
		ess_setmixer(sc, 0x78, ess_getmixer(sc, 0x78) | 0x03);
	if (play)
		ess_cmd(sc, DSP_CMD_SPKON);
	ess_unlock(sc);
	return 0;
}