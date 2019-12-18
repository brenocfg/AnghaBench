#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svm_softc {TYPE_1__* vcpu; } ;
struct svm_regctx {int dummy; } ;
struct TYPE_2__ {struct svm_regctx swctx; } ;

/* Variables and functions */

__attribute__((used)) static __inline struct svm_regctx *
svm_get_guest_regctx(struct svm_softc *sc, int vcpu)
{

	return (&(sc->vcpu[vcpu].swctx));
}