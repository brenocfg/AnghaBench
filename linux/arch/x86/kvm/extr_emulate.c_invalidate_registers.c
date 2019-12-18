#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct x86_emulate_ctxt {scalar_t__ regs_valid; scalar_t__ regs_dirty; } ;

/* Variables and functions */

__attribute__((used)) static void invalidate_registers(struct x86_emulate_ctxt *ctxt)
{
	ctxt->regs_dirty = 0;
	ctxt->regs_valid = 0;
}