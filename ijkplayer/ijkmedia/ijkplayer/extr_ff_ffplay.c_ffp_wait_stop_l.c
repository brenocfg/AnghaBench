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
struct TYPE_6__ {int /*<<< orphan*/ * is; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_stop_l (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_close (TYPE_1__*) ; 

int ffp_wait_stop_l(FFPlayer *ffp)
{
    assert(ffp);

    if (ffp->is) {
        ffp_stop_l(ffp);
        stream_close(ffp);
        ffp->is = NULL;
    }
    return 0;
}