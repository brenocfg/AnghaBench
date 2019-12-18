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
struct vlapic {int vcpuid; struct LAPIC* apic_page; int /*<<< orphan*/  vm; } ;
struct svm_softc {int /*<<< orphan*/ * apic_page; int /*<<< orphan*/  vm; } ;
struct LAPIC {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SVM_VLAPIC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct vlapic* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlapic_init (struct vlapic*) ; 

__attribute__((used)) static struct vlapic *
svm_vlapic_init(void *arg, int vcpuid)
{
	struct svm_softc *svm_sc;
	struct vlapic *vlapic;

	svm_sc = arg;
	vlapic = malloc(sizeof(struct vlapic), M_SVM_VLAPIC, M_WAITOK | M_ZERO);
	vlapic->vm = svm_sc->vm;
	vlapic->vcpuid = vcpuid;
	vlapic->apic_page = (struct LAPIC *)&svm_sc->apic_page[vcpuid];

	vlapic_init(vlapic);

	return (vlapic);
}