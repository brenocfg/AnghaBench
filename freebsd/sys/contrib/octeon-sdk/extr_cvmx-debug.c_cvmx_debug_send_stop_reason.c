#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ddbl; scalar_t__ ddbs; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_debug_register_t ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_10__ {TYPE_2__ hw_dbp; } ;
typedef  TYPE_4__ cvmx_debug_core_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_debug_putpacket_hexint (char*,int) ; 
 int /*<<< orphan*/  cvmx_debug_putpacket_noformat (char*) ; 

__attribute__((used)) static void cvmx_debug_send_stop_reason(cvmx_debug_register_t *debug_reg, volatile cvmx_debug_core_context_t *context)
{
    /* Handle Debug Data Breakpoint Store/Load Exception. */
    if (debug_reg->s.ddbs || debug_reg->s.ddbl)
        cvmx_debug_putpacket_hexint("T8:", (int) context->hw_dbp.status);
    else
        cvmx_debug_putpacket_noformat("T9");
}