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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  volatile depc; int /*<<< orphan*/  volatile cause; int /*<<< orphan*/  volatile badvaddr; int /*<<< orphan*/  volatile status; } ;
struct TYPE_5__ {TYPE_1__ cop0; int /*<<< orphan*/  volatile hi; int /*<<< orphan*/  volatile lo; int /*<<< orphan*/  volatile* regs; } ;
typedef  TYPE_2__ cvmx_debug_core_context_t ;

/* Variables and functions */

__attribute__((used)) static volatile uint64_t *cvmx_debug_regnum_to_context_ref(int regnum, volatile cvmx_debug_core_context_t *context)
{
    /* Must be kept in sync with mips_octeon_reg_names in gdb/mips-tdep.c. */
    if (regnum < 32)
        return &context->regs[regnum];
    switch (regnum)
    {
        case 32: return &context->cop0.status;
        case 33: return &context->lo;
        case 34: return &context->hi;
        case 35: return &context->cop0.badvaddr;
        case 36: return &context->cop0.cause;
        case 37: return &context->cop0.depc;
        default: return NULL;
    }
}