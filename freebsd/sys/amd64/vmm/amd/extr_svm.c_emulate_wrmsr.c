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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int ;
struct svm_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 scalar_t__ MSR_EFER ; 
 scalar_t__ lapic_msr (scalar_t__) ; 
 int lapic_wrmsr (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int svm_write_efer (struct svm_softc*,int,int /*<<< orphan*/ ,int*) ; 
 int svm_wrmsr (struct svm_softc*,int,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
emulate_wrmsr(struct svm_softc *sc, int vcpu, u_int num, uint64_t val,
    bool *retu)
{
	int error;

	if (lapic_msr(num))
		error = lapic_wrmsr(sc->vm, vcpu, num, val, retu);
	else if (num == MSR_EFER)
		error = svm_write_efer(sc, vcpu, val, retu);
	else
		error = svm_wrmsr(sc, vcpu, num, val, retu);

	return (error);
}