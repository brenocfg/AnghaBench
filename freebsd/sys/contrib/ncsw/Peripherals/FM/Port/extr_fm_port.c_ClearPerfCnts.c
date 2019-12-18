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
struct TYPE_4__ {scalar_t__ portType; } ;
typedef  TYPE_1__ t_FmPort ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_PORT_ModifyCounter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_DMA_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_FIFO_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_QUEUE_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_TASK_UTIL ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 

__attribute__((used)) static t_Error ClearPerfCnts(t_FmPort *p_FmPort)
{
    if (p_FmPort->portType != e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
        FM_PORT_ModifyCounter(p_FmPort, e_FM_PORT_COUNTERS_QUEUE_UTIL, 0);
    FM_PORT_ModifyCounter(p_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL, 0);
    FM_PORT_ModifyCounter(p_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL, 0);
    FM_PORT_ModifyCounter(p_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL, 0);
    return E_OK;
}