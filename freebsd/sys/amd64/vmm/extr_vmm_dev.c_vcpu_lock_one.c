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
struct vmmdev_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int vcpu_set_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int vm_get_maxcpus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vcpu_lock_one(struct vmmdev_softc *sc, int vcpu)
{
	int error;

	if (vcpu < 0 || vcpu >= vm_get_maxcpus(sc->vm))
		return (EINVAL);

	error = vcpu_set_state(sc->vm, vcpu, VCPU_FROZEN, true);
	return (error);
}