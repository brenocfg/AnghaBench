#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int multicoredebug; } ;
struct TYPE_5__ {int status; } ;
struct TYPE_7__ {TYPE_2__ cop0; TYPE_1__ hw_dbp; } ;
typedef  TYPE_3__ cvmx_debug_core_context_t ;

/* Variables and functions */

__attribute__((used)) static void cvmx_debug_clear_status(volatile cvmx_debug_core_context_t *context)
{
    /* SW needs to clear the BreakStatus bits after a watchpoint is hit or on
       reset.  */
    context->hw_dbp.status &= ~0x3fff;

    /* Clear MCD0, which is write-1-to-clear.  */
    context->cop0.multicoredebug |= 1;
}