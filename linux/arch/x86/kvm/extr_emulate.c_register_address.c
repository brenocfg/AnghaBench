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
struct x86_emulate_ctxt {int dummy; } ;

/* Variables and functions */
 unsigned long address_mask (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_read (struct x86_emulate_ctxt*,int) ; 

__attribute__((used)) static inline unsigned long
register_address(struct x86_emulate_ctxt *ctxt, int reg)
{
	return address_mask(ctxt, reg_read(ctxt, reg));
}