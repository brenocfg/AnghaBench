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
 int __kvm_set_dr (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 

__attribute__((used)) static int emulator_set_dr(struct x86_emulate_ctxt *ctxt, int dr,
			   unsigned long value)
{

	return __kvm_set_dr(emul_to_vcpu(ctxt), dr, value);
}