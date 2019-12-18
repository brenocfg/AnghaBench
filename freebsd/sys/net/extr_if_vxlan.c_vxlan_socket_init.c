#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;
struct vxlan_socket {int /*<<< orphan*/  vxlso_sock; TYPE_2__ vxlso_laddr; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct sockopt {int* sopt_val; int sopt_valsize; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  sopt ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOPT_SET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 
 int socreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int sosetopt (int /*<<< orphan*/ ,struct sockopt*) ; 
 int udp_set_kernel_tunneling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxlan_rcv_udp_packet ; 
 scalar_t__ vxlan_reuse_port ; 

__attribute__((used)) static int
vxlan_socket_init(struct vxlan_socket *vso, struct ifnet *ifp)
{
	struct thread *td;
	int error;

	td = curthread;

	error = socreate(vso->vxlso_laddr.sa.sa_family, &vso->vxlso_sock,
	    SOCK_DGRAM, IPPROTO_UDP, td->td_ucred, td);
	if (error) {
		if_printf(ifp, "cannot create socket: %d\n", error);
		return (error);
	}

	error = udp_set_kernel_tunneling(vso->vxlso_sock,
	    vxlan_rcv_udp_packet, NULL, vso);
	if (error) {
		if_printf(ifp, "cannot set tunneling function: %d\n", error);
		return (error);
	}

	if (vxlan_reuse_port != 0) {
		struct sockopt sopt;
		int val = 1;

		bzero(&sopt, sizeof(sopt));
		sopt.sopt_dir = SOPT_SET;
		sopt.sopt_level = IPPROTO_IP;
		sopt.sopt_name = SO_REUSEPORT;
		sopt.sopt_val = &val;
		sopt.sopt_valsize = sizeof(val);
		error = sosetopt(vso->vxlso_sock, &sopt);
		if (error) {
			if_printf(ifp,
			    "cannot set REUSEADDR socket opt: %d\n", error);
			return (error);
		}
	}

	return (0);
}