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
struct agg_rchinfo {int speed; int blklen; int /*<<< orphan*/  stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static u_int
calc_timer_div_rch(struct agg_rchinfo *ch)
{
	u_int speed;

	speed = ch->speed;
#ifdef INVARIANTS
	if (speed == 0) {
		printf("snd_maestro: rch.speed == 0, which shouldn't\n");
		speed = 1;
	}
#endif
	return (48000 * (ch->blklen << (!ch->stereo))
		+ speed - 1) / speed;
}