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
typedef  scalar_t__ uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {int sa_family; int sa_len; } ;
struct sctp_getaddresses {TYPE_1__* addr; scalar_t__ sget_assoc_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int caddr_t ;
struct TYPE_2__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int SCTP_BINDX_ADD_ADDR ; 
 int SCTP_BINDX_REM_ADDR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct sctp_getaddresses*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sctp_getaddresses*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int,struct sctp_getaddresses*,int /*<<< orphan*/ ) ; 

int
sctp_bindx(int sd, struct sockaddr *addrs, int addrcnt, int flags)
{
	struct sctp_getaddresses *gaddrs;
	struct sockaddr *sa;
	struct sockaddr_in *sin;
	struct sockaddr_in6 *sin6;
	int i;
	size_t argsz;
	uint16_t sport = 0;

	/* validate the flags */
	if ((flags != SCTP_BINDX_ADD_ADDR) &&
	    (flags != SCTP_BINDX_REM_ADDR)) {
		errno = EFAULT;
		return (-1);
	}
	/* validate the address count and list */
	if ((addrcnt <= 0) || (addrs == NULL)) {
		errno = EINVAL;
		return (-1);
	}
	/* First pre-screen the addresses */
	sa = addrs;
	for (i = 0; i < addrcnt; i++) {
		switch (sa->sa_family) {
		case AF_INET:
			if (sa->sa_len != sizeof(struct sockaddr_in)) {
				errno = EINVAL;
				return (-1);
			}
			sin = (struct sockaddr_in *)sa;
			if (sin->sin_port) {
				/* non-zero port, check or save */
				if (sport) {
					/* Check against our port */
					if (sport != sin->sin_port) {
						errno = EINVAL;
						return (-1);
					}
				} else {
					/* save off the port */
					sport = sin->sin_port;
				}
			}
			break;
		case AF_INET6:
			if (sa->sa_len != sizeof(struct sockaddr_in6)) {
				errno = EINVAL;
				return (-1);
			}
			sin6 = (struct sockaddr_in6 *)sa;
			if (sin6->sin6_port) {
				/* non-zero port, check or save */
				if (sport) {
					/* Check against our port */
					if (sport != sin6->sin6_port) {
						errno = EINVAL;
						return (-1);
					}
				} else {
					/* save off the port */
					sport = sin6->sin6_port;
				}
			}
			break;
		default:
			/* Invalid address family specified. */
			errno = EAFNOSUPPORT;
			return (-1);
		}
		sa = (struct sockaddr *)((caddr_t)sa + sa->sa_len);
	}
	argsz = sizeof(struct sctp_getaddresses) +
	    sizeof(struct sockaddr_storage);
	if ((gaddrs = (struct sctp_getaddresses *)malloc(argsz)) == NULL) {
		errno = ENOMEM;
		return (-1);
	}
	sa = addrs;
	for (i = 0; i < addrcnt; i++) {
		memset(gaddrs, 0, argsz);
		gaddrs->sget_assoc_id = 0;
		memcpy(gaddrs->addr, sa, sa->sa_len);
		/*
		 * Now, if there was a port mentioned, assure that the first
		 * address has that port to make sure it fails or succeeds
		 * correctly.
		 */
		if ((i == 0) && (sport != 0)) {
			switch (gaddrs->addr->sa_family) {
			case AF_INET:
				sin = (struct sockaddr_in *)gaddrs->addr;
				sin->sin_port = sport;
				break;
			case AF_INET6:
				sin6 = (struct sockaddr_in6 *)gaddrs->addr;
				sin6->sin6_port = sport;
				break;
			}
		}
		if (setsockopt(sd, IPPROTO_SCTP, flags, gaddrs,
		    (socklen_t) argsz) != 0) {
			free(gaddrs);
			return (-1);
		}
		sa = (struct sockaddr *)((caddr_t)sa + sa->sa_len);
	}
	free(gaddrs);
	return (0);
}