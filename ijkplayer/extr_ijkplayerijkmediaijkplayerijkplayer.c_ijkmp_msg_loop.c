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
struct TYPE_2__ {int (* msg_loop ) (void*) ;} ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int stub1 (void*) ; 

__attribute__((used)) static int ijkmp_msg_loop(void *arg)
{
    IjkMediaPlayer *mp = arg;
    int ret = mp->msg_loop(arg);
    return ret;
}