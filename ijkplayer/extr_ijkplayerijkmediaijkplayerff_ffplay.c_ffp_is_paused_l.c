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
struct TYPE_5__ {int paused; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_6__ {TYPE_1__* is; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

int ffp_is_paused_l(FFPlayer *ffp)
{
    assert(ffp);
    VideoState *is = ffp->is;
    if (!is)
        return 1;

    return is->paused;
}