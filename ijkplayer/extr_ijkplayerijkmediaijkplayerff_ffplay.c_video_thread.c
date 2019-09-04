#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ node_vdec; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int ffpipenode_run_sync (scalar_t__) ; 

__attribute__((used)) static int video_thread(void *arg)
{
    FFPlayer *ffp = (FFPlayer *)arg;
    int       ret = 0;

    if (ffp->node_vdec) {
        ret = ffpipenode_run_sync(ffp->node_vdec);
    }
    return ret;
}