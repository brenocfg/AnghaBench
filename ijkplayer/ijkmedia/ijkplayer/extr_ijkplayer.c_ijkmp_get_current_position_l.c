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
struct TYPE_3__ {long seek_msec; int /*<<< orphan*/  ffplayer; scalar_t__ seek_req; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 long ffp_get_current_position_l (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ijkmp_get_current_position_l(IjkMediaPlayer *mp)
{
    if (mp->seek_req)
        return mp->seek_msec;
    return ffp_get_current_position_l(mp->ffplayer);
}