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
struct svm_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCB_CTRL1_INTCPT ; 
 int /*<<< orphan*/  VMCB_INTCPT_IRET ; 
 int /*<<< orphan*/  nmi_blocked (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_enable_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_nmi_blocking(struct svm_softc *sc, int vcpu)
{

	KASSERT(!nmi_blocked(sc, vcpu), ("vNMI already blocked"));
	VCPU_CTR0(sc->vm, vcpu, "vNMI blocking enabled");
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_IRET);
}