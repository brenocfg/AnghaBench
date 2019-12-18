#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mp_state; int /*<<< orphan*/  ffplayer; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_MSG_PLAYBACK_STATE_CHANGED ; 
 int /*<<< orphan*/  ffp_notify_msg1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ijkmp_change_state_l(IjkMediaPlayer *mp, int new_state)
{
    mp->mp_state = new_state;
    ffp_notify_msg1(mp->ffplayer, FFP_MSG_PLAYBACK_STATE_CHANGED);
}