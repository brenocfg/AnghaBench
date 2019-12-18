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
typedef  int /*<<< orphan*/  v6only ;
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct linux_socket_args {int type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  hdrincl ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int LINUX_SOCK_MAX ; 
 int LINUX_SOCK_TYPE_MASK ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int SOCK_RAW ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  kern_setsockopt (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int kern_socket (struct thread*,int,int,int /*<<< orphan*/ ) ; 
 int linux_set_socket_flags (int,int*) ; 
 int linux_to_bsd_domain (int /*<<< orphan*/ ) ; 

int
linux_socket(struct thread *td, struct linux_socket_args *args)
{
	int domain, retval_socket, type;

	type = args->type & LINUX_SOCK_TYPE_MASK;
	if (type < 0 || type > LINUX_SOCK_MAX)
		return (EINVAL);
	retval_socket = linux_set_socket_flags(args->type & ~LINUX_SOCK_TYPE_MASK,
		&type);
	if (retval_socket != 0)
		return (retval_socket);
	domain = linux_to_bsd_domain(args->domain);
	if (domain == -1)
		return (EAFNOSUPPORT);

	retval_socket = kern_socket(td, domain, type, args->protocol);
	if (retval_socket)
		return (retval_socket);

	if (type == SOCK_RAW
	    && (args->protocol == IPPROTO_RAW || args->protocol == 0)
	    && domain == PF_INET) {
		/* It's a raw IP socket: set the IP_HDRINCL option. */
		int hdrincl;

		hdrincl = 1;
		/* We ignore any error returned by kern_setsockopt() */
		kern_setsockopt(td, td->td_retval[0], IPPROTO_IP, IP_HDRINCL,
		    &hdrincl, UIO_SYSSPACE, sizeof(hdrincl));
	}
#ifdef INET6
	/*
	 * Linux AF_INET6 socket has IPV6_V6ONLY setsockopt set to 0 by default
	 * and some apps depend on this. So, set V6ONLY to 0 for Linux apps.
	 * For simplicity we do this unconditionally of the net.inet6.ip6.v6only
	 * sysctl value.
	 */
	if (domain == PF_INET6) {
		int v6only;

		v6only = 0;
		/* We ignore any error returned by setsockopt() */
		kern_setsockopt(td, td->td_retval[0], IPPROTO_IPV6, IPV6_V6ONLY,
		    &v6only, UIO_SYSSPACE, sizeof(v6only));
	}
#endif

	return (retval_socket);
}