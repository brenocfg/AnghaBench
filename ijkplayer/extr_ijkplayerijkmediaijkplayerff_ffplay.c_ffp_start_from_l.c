#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VideoState ;
struct TYPE_6__ {int auto_resume; int /*<<< orphan*/ * is; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int EIJK_NULL_IS_PTR ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_seek_to_l (TYPE_1__*,long) ; 
 int /*<<< orphan*/  ffp_toggle_buffering (TYPE_1__*,int) ; 

int ffp_start_from_l(FFPlayer *ffp, long msec)
{
    assert(ffp);
    VideoState *is = ffp->is;
    if (!is)
        return EIJK_NULL_IS_PTR;

    ffp->auto_resume = 1;
    ffp_toggle_buffering(ffp, 1);
    ffp_seek_to_l(ffp, msec);
    return 0;
}