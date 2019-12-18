#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int seek_req; long seek_msec; int /*<<< orphan*/  ffplayer; int /*<<< orphan*/  mp_state; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_REQ_SEEK ; 
 int /*<<< orphan*/  MP_RET_IF_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_notify_msg2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffp_remove_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikjmp_chkst_seek_l (int /*<<< orphan*/ ) ; 

int ijkmp_seek_to_l(IjkMediaPlayer *mp, long msec)
{
    assert(mp);

    MP_RET_IF_FAILED(ikjmp_chkst_seek_l(mp->mp_state));

    mp->seek_req = 1;
    mp->seek_msec = msec;
    ffp_remove_msg(mp->ffplayer, FFP_REQ_SEEK);
    ffp_notify_msg2(mp->ffplayer, FFP_REQ_SEEK, (int)msec);
    // TODO: 9 64-bit long?

    return 0;
}