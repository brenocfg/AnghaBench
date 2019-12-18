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
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_IDLE ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int,int) ; 
 int vcpu_get_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_set_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcpu_unlock_one(struct vmmdev_softc *sc, int vcpu)
{
	enum vcpu_state state;

	state = vcpu_get_state(sc->vm, vcpu, NULL);
	if (state != VCPU_FROZEN) {
		panic("vcpu %s(%d) has invalid state %d", vm_name(sc->vm),
		    vcpu, state);
	}

	vcpu_set_state(sc->vm, vcpu, VCPU_IDLE, false);
}