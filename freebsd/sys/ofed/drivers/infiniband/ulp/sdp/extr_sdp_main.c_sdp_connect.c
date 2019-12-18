#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_len; } ;
struct sdp_sock {int flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 scalar_t__ IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int prison_remote_ip4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int sdp_start_connect (struct sdp_sock*,struct sockaddr*,struct thread*) ; 

__attribute__((used)) static int
sdp_connect(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	int error = 0;
	struct sdp_sock *ssk;
	struct sockaddr_in *sin;

	sin = (struct sockaddr_in *)nam;
	if (nam->sa_len != sizeof (*sin))
		return (EINVAL);
	if (sin->sin_family != AF_INET)
		return (EINVAL);
	if (IN_MULTICAST(ntohl(sin->sin_addr.s_addr)))
		return (EAFNOSUPPORT);
	if ((error = prison_remote_ip4(td->td_ucred, &sin->sin_addr)) != 0)
		return (error);
	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DROPPED))
		error = EINVAL;
	else
		error = sdp_start_connect(ssk, nam, td);
	SDP_WUNLOCK(ssk);
	return (error);
}