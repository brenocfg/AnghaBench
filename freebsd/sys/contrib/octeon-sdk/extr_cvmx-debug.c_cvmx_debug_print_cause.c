#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int multicoredebug; int debug; } ;
struct TYPE_5__ {TYPE_1__ cop0; } ;
typedef  TYPE_2__ cvmx_debug_core_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_DEBUG_LOGGING ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 

__attribute__((used)) static inline void cvmx_debug_print_cause(volatile cvmx_debug_core_context_t *context)
{
    if (!CVMX_DEBUG_LOGGING)
        return;
    if (context->cop0.multicoredebug & 1)
        cvmx_dprintf("MCD0 was pulsed\n");
    if (context->cop0.multicoredebug & (1 << 16))
        cvmx_dprintf("Exception %lld in Debug Mode\n", (long long)((context->cop0.debug >> 10) & 0x1f));
    if (context->cop0.debug & (1 << 19))
        cvmx_dprintf("DDBSImpr\n");
    if (context->cop0.debug & (1 << 18))
        cvmx_dprintf("DDBLImpr\n");
    if (context->cop0.debug & (1 << 5))
        cvmx_dprintf("DINT\n");
    if (context->cop0.debug & (1 << 4))
        cvmx_dprintf("Debug Instruction Breakpoint (DIB) exception\n");
    if (context->cop0.debug & (1 << 3))
        cvmx_dprintf("Debug Date Break Store (DDBS) exception\n");
    if (context->cop0.debug & (1 << 2))
        cvmx_dprintf("Debug Date Break Load (DDBL) exception\n");
    if (context->cop0.debug & (1 << 1))
        cvmx_dprintf("Debug Breakpoint (DBp) exception\n");
    if (context->cop0.debug & (1 << 0))
        cvmx_dprintf("Debug Single Step (DSS) exception\n");
}