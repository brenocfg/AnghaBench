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
typedef  scalar_t__ ulong ;
struct x86_emulate_ctxt {int /*<<< orphan*/  ad_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assign_register (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* reg_rmw (struct x86_emulate_ctxt*,int) ; 

__attribute__((used)) static inline void
register_address_increment(struct x86_emulate_ctxt *ctxt, int reg, int inc)
{
	ulong *preg = reg_rmw(ctxt, reg);

	assign_register(preg, *preg + inc, ctxt->ad_bytes);
}