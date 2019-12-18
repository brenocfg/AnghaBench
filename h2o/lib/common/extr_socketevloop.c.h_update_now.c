#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int _now_nanosec; int _now_millisec; TYPE_3__ _tv_at; } ;
typedef  TYPE_1__ h2o_evloop_t ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (TYPE_3__*,int /*<<< orphan*/ *) ; 

void update_now(h2o_evloop_t *loop)
{
    gettimeofday(&loop->_tv_at, NULL);
    loop->_now_nanosec = ((uint64_t)loop->_tv_at.tv_sec * 1000000 + loop->_tv_at.tv_usec) * 1000;
    loop->_now_millisec = loop->_now_nanosec / 1000000;
}