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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int EACCES ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
#define  EHOSTDOWN 131 
#define  EHOSTUNREACH 130 
 int EINVAL ; 
#define  ENETDOWN 129 
#define  ENETUNREACH 128 
 int EPERM ; 
 scalar_t__ VERB_ALGO ; 
 scalar_t__ VERB_DETAIL ; 
 scalar_t__ addr_is_broadcast (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ addr_is_ip4mapped (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
udp_send_errno_needs_log(struct sockaddr* addr, socklen_t addrlen)
{
	/* do not log transient errors (unless high verbosity) */
#if defined(ENETUNREACH) || defined(EHOSTDOWN) || defined(EHOSTUNREACH) || defined(ENETDOWN)
	switch(errno) {
#  ifdef ENETUNREACH
		case ENETUNREACH:
#  endif
#  ifdef EHOSTDOWN
		case EHOSTDOWN:
#  endif
#  ifdef EHOSTUNREACH
		case EHOSTUNREACH:
#  endif
#  ifdef ENETDOWN
		case ENETDOWN:
#  endif
			if(verbosity < VERB_ALGO)
				return 0;
		default:
			break;
	}
#endif
	/* permission denied is gotten for every send if the
	 * network is disconnected (on some OS), squelch it */
	if( ((errno == EPERM)
#  ifdef EADDRNOTAVAIL
		/* 'Cannot assign requested address' also when disconnected */
		|| (errno == EADDRNOTAVAIL)
#  endif
		) && verbosity < VERB_DETAIL)
		return 0;
#  ifdef EADDRINUSE
	/* If SO_REUSEADDR is set, we could try to connect to the same server
	 * from the same source port twice. */
	if(errno == EADDRINUSE && verbosity < VERB_DETAIL)
		return 0;
#  endif
	/* squelch errors where people deploy AAAA ::ffff:bla for
	 * authority servers, which we try for intranets. */
	if(errno == EINVAL && addr_is_ip4mapped(
		(struct sockaddr_storage*)addr, addrlen) &&
		verbosity < VERB_DETAIL)
		return 0;
	/* SO_BROADCAST sockopt can give access to 255.255.255.255,
	 * but a dns cache does not need it. */
	if(errno == EACCES && addr_is_broadcast(
		(struct sockaddr_storage*)addr, addrlen) &&
		verbosity < VERB_DETAIL)
		return 0;
	return 1;
}