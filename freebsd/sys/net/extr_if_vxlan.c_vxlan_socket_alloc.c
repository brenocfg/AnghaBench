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
typedef  union vxlan_sockaddr {int dummy; } vxlan_sockaddr ;
struct vxlan_socket {union vxlan_sockaddr vxlso_laddr; int /*<<< orphan*/ * vxlso_vni_hash; int /*<<< orphan*/  vxlso_refcnt; int /*<<< orphan*/  vxlso_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_VXLAN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int VXLAN_SO_VNI_HASH_SIZE ; 
 struct vxlan_socket* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct vxlan_socket *
vxlan_socket_alloc(const union vxlan_sockaddr *sa)
{
	struct vxlan_socket *vso;
	int i;

	vso = malloc(sizeof(*vso), M_VXLAN, M_WAITOK | M_ZERO);
	rm_init(&vso->vxlso_lock, "vxlansorm");
	refcount_init(&vso->vxlso_refcnt, 0);
	for (i = 0; i < VXLAN_SO_VNI_HASH_SIZE; i++)
		LIST_INIT(&vso->vxlso_vni_hash[i]);
	vso->vxlso_laddr = *sa;

	return (vso);
}