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
typedef  int u_char ;
struct sb_info {int bd_id; int /*<<< orphan*/  bd_flags; } ;
struct sb_chinfo {scalar_t__ dir; int spd; int /*<<< orphan*/  fmt; struct sb_info* parent; } ;

/* Variables and functions */
 int AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BD_F_HISPEED ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  sb_cmd1 (struct sb_info*,int,int) ; 
 int /*<<< orphan*/  sb_lock (struct sb_info*) ; 
 int /*<<< orphan*/  sb_unlock (struct sb_info*) ; 

__attribute__((used)) static int
sb_speed(struct sb_chinfo *ch)
{
	struct sb_info *sb = ch->parent;
    	int play = (ch->dir == PCMDIR_PLAY)? 1 : 0;
	int stereo = (AFMT_CHANNEL(ch->fmt) > 1)? 1 : 0;
	int speed, tmp, thresh, max;
	u_char tconst;

	if (sb->bd_id >= 0x300) {
		thresh = stereo? 11025 : 23000;
		max = stereo? 22050 : 44100;
	} else if (sb->bd_id > 0x200) {
		thresh = play? 23000 : 13000;
		max = play? 44100 : 15000;
	} else {
		thresh = 999999;
		max = play? 23000 : 13000;
	}

	speed = ch->spd;
	if (speed > max)
		speed = max;

	sb_lock(sb);
	sb->bd_flags &= ~BD_F_HISPEED;
	if (speed > thresh)
		sb->bd_flags |= BD_F_HISPEED;

	tmp = 65536 - (256000000 / (speed << stereo));
	tconst = tmp >> 8;

	sb_cmd1(sb, 0x40, tconst); /* set time constant */

	speed = (256000000 / (65536 - tmp)) >> stereo;

	ch->spd = speed;
	sb_unlock(sb);
	return speed;
}