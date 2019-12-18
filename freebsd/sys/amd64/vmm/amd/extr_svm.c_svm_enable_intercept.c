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
struct svm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  svm_set_intercept (struct svm_softc*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
svm_enable_intercept(struct svm_softc *sc, int vcpu, int off, uint32_t bitmask)
{

	svm_set_intercept(sc, vcpu, off, bitmask, 1);
}