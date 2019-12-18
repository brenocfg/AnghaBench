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
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  kvm_emulate_wbinvd_noskip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emulator_wbinvd(struct x86_emulate_ctxt *ctxt)
{
	kvm_emulate_wbinvd_noskip(emul_to_vcpu(ctxt));
}