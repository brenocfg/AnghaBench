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
typedef  int uint16_t ;
struct vmmdev_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_unlock_one (struct vmmdev_softc*,int) ; 
 int vm_get_maxcpus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcpu_unlock_all(struct vmmdev_softc *sc)
{
	int vcpu;
	uint16_t maxcpus;

	maxcpus = vm_get_maxcpus(sc->vm);
	for (vcpu = 0; vcpu < maxcpus; vcpu++)
		vcpu_unlock_one(sc, vcpu);
}