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
typedef  int /*<<< orphan*/  uint32_t ;
struct svm_vcpu {int /*<<< orphan*/  dirty; } ;
struct svm_softc {int dummy; } ;

/* Variables and functions */
 struct svm_vcpu* svm_get_vcpu (struct svm_softc*,int) ; 

__attribute__((used)) static __inline void
svm_set_dirty(struct svm_softc *sc, int vcpu, uint32_t dirtybits)
{
        struct svm_vcpu *vcpustate;

        vcpustate = svm_get_vcpu(sc, vcpu);

        vcpustate->dirty |= dirtybits;
}