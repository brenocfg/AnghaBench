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
struct svm_vcpu {int dummy; } ;
struct svm_softc {struct svm_vcpu* vcpu; } ;

/* Variables and functions */

__attribute__((used)) static __inline struct svm_vcpu *
svm_get_vcpu(struct svm_softc *sc, int vcpu)
{

	return (&(sc->vcpu[vcpu]));
}