#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmcb_ctrl {int dummy; } ;
struct svm_softc {TYPE_2__* vcpu; } ;
struct TYPE_3__ {struct vmcb_ctrl ctrl; } ;
struct TYPE_4__ {TYPE_1__ vmcb; } ;

/* Variables and functions */

__attribute__((used)) static __inline struct vmcb_ctrl *
svm_get_vmcb_ctrl(struct svm_softc *sc, int vcpu)
{

	return (&(sc->vcpu[vcpu].vmcb.ctrl));
}