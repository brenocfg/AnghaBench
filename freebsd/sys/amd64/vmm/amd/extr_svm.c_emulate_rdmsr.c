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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vmcb_state {int rax; } ;
struct svm_softc {int /*<<< orphan*/  vm; } ;
struct svm_regctx {int sctx_rdx; } ;

/* Variables and functions */
 scalar_t__ lapic_msr (int /*<<< orphan*/ ) ; 
 int lapic_rdmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 struct svm_regctx* svm_get_guest_regctx (struct svm_softc*,int) ; 
 struct vmcb_state* svm_get_vmcb_state (struct svm_softc*,int) ; 
 int svm_rdmsr (struct svm_softc*,int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int
emulate_rdmsr(struct svm_softc *sc, int vcpu, u_int num, bool *retu)
{
	struct vmcb_state *state;
	struct svm_regctx *ctx;
	uint64_t result;
	int error;

	if (lapic_msr(num))
		error = lapic_rdmsr(sc->vm, vcpu, num, &result, retu);
	else
		error = svm_rdmsr(sc, vcpu, num, &result, retu);

	if (error == 0) {
		state = svm_get_vmcb_state(sc, vcpu);
		ctx = svm_get_guest_regctx(sc, vcpu);
		state->rax = result & 0xffffffff;
		ctx->sctx_rdx = result >> 32;
	}

	return (error);
}