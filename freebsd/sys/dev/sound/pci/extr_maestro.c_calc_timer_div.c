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
typedef  int u_int ;
struct agg_chinfo {int speed; int num; int blklen; int /*<<< orphan*/  stereo; int /*<<< orphan*/  qs16; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static u_int
calc_timer_div(struct agg_chinfo *ch)
{
	u_int speed;

	speed = ch->speed;
#ifdef INVARIANTS
	if (speed == 0) {
		printf("snd_maestro: pch[%d].speed == 0, which shouldn't\n",
		       ch->num);
		speed = 1;
	}
#endif
	return (48000 * (ch->blklen << (!ch->qs16 + !ch->stereo))
		+ speed - 1) / speed;
}