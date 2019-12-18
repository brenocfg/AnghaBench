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
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sctp_sndrcvinfo {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sndrcvninfo ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_SNDRCV ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 scalar_t__ sctp_find_cmsg (int /*<<< orphan*/ ,void*,struct mbuf*,int) ; 
 int sctp_lower_sosend (struct socket*,struct sockaddr*,struct uio*,struct mbuf*,struct mbuf*,int,struct sctp_sndrcvinfo*,struct thread*) ; 

int
sctp_sosend(struct socket *so,
    struct sockaddr *addr,
    struct uio *uio,
    struct mbuf *top,
    struct mbuf *control,
    int flags,
    struct thread *p
)
{
	int error, use_sndinfo = 0;
	struct sctp_sndrcvinfo sndrcvninfo;
	struct sockaddr *addr_to_use;
#if defined(INET) && defined(INET6)
	struct sockaddr_in sin;
#endif

	if (control) {
		/* process cmsg snd/rcv info (maybe a assoc-id) */
		if (sctp_find_cmsg(SCTP_SNDRCV, (void *)&sndrcvninfo, control,
		    sizeof(sndrcvninfo))) {
			/* got one */
			use_sndinfo = 1;
		}
	}
	addr_to_use = addr;
#if defined(INET) && defined(INET6)
	if ((addr) && (addr->sa_family == AF_INET6)) {
		struct sockaddr_in6 *sin6;

		sin6 = (struct sockaddr_in6 *)addr;
		if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
			in6_sin6_2_sin(&sin, sin6);
			addr_to_use = (struct sockaddr *)&sin;
		}
	}
#endif
	error = sctp_lower_sosend(so, addr_to_use, uio, top,
	    control,
	    flags,
	    use_sndinfo ? &sndrcvninfo : NULL
	    ,p
	    );
	return (error);
}