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
struct svm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_CTRL1_INTCPT ; 
 int /*<<< orphan*/  VMCB_INTCPT_IRET ; 
 int svm_get_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nmi_blocked(struct svm_softc *sc, int vcpu)
{
	int blocked;

	blocked = svm_get_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
	    VMCB_INTCPT_IRET);
	return (blocked);
}