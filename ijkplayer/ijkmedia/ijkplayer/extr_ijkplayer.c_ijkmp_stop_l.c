#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ffplayer; int /*<<< orphan*/  mp_state; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_REQ_PAUSE ; 
 int /*<<< orphan*/  FFP_REQ_START ; 
 int /*<<< orphan*/  MPST_RET_IF_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_STATE_END ; 
 int /*<<< orphan*/  MP_STATE_ERROR ; 
 int /*<<< orphan*/  MP_STATE_IDLE ; 
 int /*<<< orphan*/  MP_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MP_STATE_STOPPED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_remove_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffp_stop_l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkmp_change_state_l (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ijkmp_stop_l(IjkMediaPlayer *mp)
{
    assert(mp);

    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_IDLE);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_INITIALIZED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_ASYNC_PREPARING);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_PREPARED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_STARTED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_PAUSED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_COMPLETED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_STOPPED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_ERROR);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_END);

    ffp_remove_msg(mp->ffplayer, FFP_REQ_START);
    ffp_remove_msg(mp->ffplayer, FFP_REQ_PAUSE);
    int retval = ffp_stop_l(mp->ffplayer);
    if (retval < 0) {
        return retval;
    }

    ijkmp_change_state_l(mp, MP_STATE_STOPPED);
    return 0;
}