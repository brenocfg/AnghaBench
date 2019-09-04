#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ buffering_on; scalar_t__ pause_req; int /*<<< orphan*/  step; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_6__ {TYPE_1__* is; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  stream_toggle_pause_l (TYPE_2__*,int) ; 

__attribute__((used)) static void stream_update_pause_l(FFPlayer *ffp)
{
    VideoState *is = ffp->is;
    if (!is->step && (is->pause_req || is->buffering_on)) {
        stream_toggle_pause_l(ffp, 1);
    } else {
        stream_toggle_pause_l(ffp, 0);
    }
}