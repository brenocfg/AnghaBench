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
struct vxlan_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ VXLAN_RELEASE (struct vxlan_softc*) ; 
 int /*<<< orphan*/  wakeup (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_release(struct vxlan_softc *sc)
{

	/*
	 * The softc may be destroyed as soon as we release our reference,
	 * so we cannot serialize the wakeup with the softc lock. We use a
	 * timeout in our sleeps so a missed wakeup is unfortunate but not
	 * fatal.
	 */
	if (VXLAN_RELEASE(sc) != 0)
		wakeup(sc);
}