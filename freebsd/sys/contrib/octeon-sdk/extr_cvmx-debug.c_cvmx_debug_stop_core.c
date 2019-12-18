#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int core_finished; } ;
typedef  TYPE_2__ cvmx_debug_state_t ;
struct TYPE_7__ {int dint; scalar_t__ sst; int /*<<< orphan*/  dss; int /*<<< orphan*/  dbp; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_debug_register_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_debug_active_core (TYPE_2__,unsigned int) ; 
 int /*<<< orphan*/  cvmx_debug_printf (char*,unsigned int) ; 

__attribute__((used)) static int cvmx_debug_stop_core(cvmx_debug_state_t state, unsigned core, cvmx_debug_register_t *debug_reg, int proxy)
{
    if (!cvmx_debug_active_core(state, core) && !debug_reg->s.dbp && !debug_reg->s.dss && (debug_reg->s.dint != 1))
    {
        debug_reg->s.sst = 0;
        cvmx_debug_printf("Core #%d not in active cores, continuing.\n", core);
        return 0;
    }
    if ((state.core_finished & (1u<<core)) && proxy)
      return 0;
    return 1;
}