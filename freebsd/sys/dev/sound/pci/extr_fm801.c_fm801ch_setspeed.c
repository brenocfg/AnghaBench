#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_5__ {scalar_t__ spd; } ;
struct TYPE_4__ {scalar_t__ spd; } ;
struct fm801_info {int play_shift; int rec_shift; TYPE_2__ rch; TYPE_1__ pch; } ;
struct fm801_chinfo {scalar_t__ dir; scalar_t__ spd; struct fm801_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_6__ {scalar_t__ limit; scalar_t__ rate; } ;

/* Variables and functions */
 int FM_PLAY_RATE_MASK ; 
 int FM_REC_RATE_MASK ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ PCMDIR_REC ; 
 TYPE_3__* fm801_rates ; 

__attribute__((used)) static u_int32_t
fm801ch_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct fm801_chinfo *ch = data;
	struct fm801_info *fm801 = ch->parent;
	int i;


	for (i = 0; i < 10 && fm801_rates[i].limit <= speed; i++) ;

	if(ch->dir == PCMDIR_PLAY) {
		fm801->pch.spd = fm801_rates[i].rate;
		fm801->play_shift = (i<<8);
		fm801->play_shift &= FM_PLAY_RATE_MASK;
	}

	if(ch->dir == PCMDIR_REC ) {
		fm801->rch.spd = fm801_rates[i].rate;
		fm801->rec_shift = (i<<8);
		fm801->rec_shift &= FM_REC_RATE_MASK;
	}

	ch->spd = fm801_rates[i].rate;

	return fm801_rates[i].rate;
}