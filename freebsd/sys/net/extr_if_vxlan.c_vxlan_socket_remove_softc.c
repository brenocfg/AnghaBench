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
struct vxlan_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct vxlan_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXLAN_SO_WLOCK (struct vxlan_socket*) ; 
 int /*<<< orphan*/  VXLAN_SO_WUNLOCK (struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxl_entry ; 
 int /*<<< orphan*/  vxlan_release (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_socket_remove_softc(struct vxlan_socket *vso, struct vxlan_softc *sc)
{

	VXLAN_SO_WLOCK(vso);
	LIST_REMOVE(sc, vxl_entry);
	VXLAN_SO_WUNLOCK(vso);

	vxlan_release(sc);
}