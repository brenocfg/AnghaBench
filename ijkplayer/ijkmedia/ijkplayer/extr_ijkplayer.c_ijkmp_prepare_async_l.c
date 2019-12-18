#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  msg_queue; } ;
struct TYPE_9__ {struct TYPE_9__* data_source; TYPE_5__* ffplayer; int /*<<< orphan*/  _msg_thread; int /*<<< orphan*/  msg_thread; int /*<<< orphan*/  mp_state; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  MPST_RET_IF_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_STATE_ASYNC_PREPARING ; 
 int /*<<< orphan*/  MP_STATE_COMPLETED ; 
 int /*<<< orphan*/  MP_STATE_END ; 
 int /*<<< orphan*/  MP_STATE_ERROR ; 
 int /*<<< orphan*/  MP_STATE_IDLE ; 
 int /*<<< orphan*/  MP_STATE_PAUSED ; 
 int /*<<< orphan*/  MP_STATE_PREPARED ; 
 int /*<<< orphan*/  MP_STATE_STARTED ; 
 int /*<<< orphan*/  SDL_CreateThreadEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int ffp_prepare_async_l (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ijkmp_change_state_l (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkmp_inc_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  ijkmp_msg_loop ; 
 int /*<<< orphan*/  msg_queue_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijkmp_prepare_async_l(IjkMediaPlayer *mp)
{
    assert(mp);

    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_IDLE);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_INITIALIZED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_ASYNC_PREPARING);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_PREPARED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_STARTED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_PAUSED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_COMPLETED);
    // MPST_RET_IF_EQ(mp->mp_state, MP_STATE_STOPPED);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_ERROR);
    MPST_RET_IF_EQ(mp->mp_state, MP_STATE_END);

    assert(mp->data_source);

    ijkmp_change_state_l(mp, MP_STATE_ASYNC_PREPARING);

    msg_queue_start(&mp->ffplayer->msg_queue);

    // released in msg_loop
    ijkmp_inc_ref(mp);
    mp->msg_thread = SDL_CreateThreadEx(&mp->_msg_thread, ijkmp_msg_loop, mp, "ff_msg_loop");
    // msg_thread is detached inside msg_loop
    // TODO: 9 release weak_thiz if pthread_create() failed;

    int retval = ffp_prepare_async_l(mp->ffplayer, mp->data_source);
    if (retval < 0) {
        ijkmp_change_state_l(mp, MP_STATE_ERROR);
        return retval;
    }

    return 0;
}