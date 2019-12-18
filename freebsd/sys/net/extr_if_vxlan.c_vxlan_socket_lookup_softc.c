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
struct vxlan_softc {int dummy; } ;
struct vxlan_socket {int dummy; } ;
struct rm_priotracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXLAN_SO_RLOCK (struct vxlan_socket*,struct rm_priotracker*) ; 
 int /*<<< orphan*/  VXLAN_SO_RUNLOCK (struct vxlan_socket*,struct rm_priotracker*) ; 
 struct vxlan_softc* vxlan_socket_lookup_softc_locked (struct vxlan_socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vxlan_softc *
vxlan_socket_lookup_softc(struct vxlan_socket *vso, uint32_t vni)
{
	struct rm_priotracker tracker;
	struct vxlan_softc *sc;

	VXLAN_SO_RLOCK(vso, &tracker);
	sc = vxlan_socket_lookup_softc_locked(vso, vni);
	VXLAN_SO_RUNLOCK(vso, &tracker);

	return (sc);
}