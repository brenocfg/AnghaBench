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
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct vxlan_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXLAN_LIST_LOCK () ; 
 int /*<<< orphan*/  VXLAN_LIST_UNLOCK () ; 
 int /*<<< orphan*/  VXLAN_SO_ACQUIRE (struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxlan_socket_list ; 
 int /*<<< orphan*/  vxlso_entry ; 

__attribute__((used)) static void
vxlan_socket_insert(struct vxlan_socket *vso)
{

	VXLAN_LIST_LOCK();
	VXLAN_SO_ACQUIRE(vso);
	LIST_INSERT_HEAD(&vxlan_socket_list, vso, vxlso_entry);
	VXLAN_LIST_UNLOCK();
}