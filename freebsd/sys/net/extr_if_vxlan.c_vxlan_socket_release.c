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
struct vxlan_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct vxlan_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXLAN_LIST_LOCK () ; 
 int /*<<< orphan*/  VXLAN_LIST_UNLOCK () ; 
 int VXLAN_SO_RELEASE (struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxlan_socket_destroy (struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxlso_entry ; 

__attribute__((used)) static void
vxlan_socket_release(struct vxlan_socket *vso)
{
	int destroy;

	VXLAN_LIST_LOCK();
	destroy = VXLAN_SO_RELEASE(vso);
	if (destroy != 0)
		LIST_REMOVE(vso, vxlso_entry);
	VXLAN_LIST_UNLOCK();

	if (destroy != 0)
		vxlan_socket_destroy(vso);
}