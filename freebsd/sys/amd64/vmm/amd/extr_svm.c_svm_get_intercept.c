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
typedef  int uint32_t ;
struct vmcb_ctrl {int* intercept; } ;
struct svm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct vmcb_ctrl* svm_get_vmcb_ctrl (struct svm_softc*,int) ; 

__attribute__((used)) static __inline int
svm_get_intercept(struct svm_softc *sc, int vcpu, int idx, uint32_t bitmask)
{
	struct vmcb_ctrl *ctrl;

	KASSERT(idx >=0 && idx < 5, ("invalid intercept index %d", idx));

	ctrl = svm_get_vmcb_ctrl(sc, vcpu);
	return (ctrl->intercept[idx] & bitmask ? 1 : 0);
}