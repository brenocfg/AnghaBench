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
struct TYPE_2__ {struct sockaddr_in* s6_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; TYPE_1__ sin6_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; } ;
struct addrinfo {scalar_t__ ai_family; int ai_addrlen; int /*<<< orphan*/ * ai_addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

void
ai_unmapped(struct addrinfo *ai)
{
#ifdef INET6
	struct sockaddr_in6 *sin6;
	struct sockaddr_in sin;
	socklen_t len;

	if (ai->ai_family != AF_INET6)
		return;
	if (ai->ai_addrlen != sizeof(struct sockaddr_in6) ||
	    sizeof(sin) > ai->ai_addrlen)
		return;
	sin6 = (struct sockaddr_in6 *)ai->ai_addr;
	if (!IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr))
		return;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	len = sizeof(struct sockaddr_in);
	memcpy(&sin.sin_addr, &sin6->sin6_addr.s6_addr[12],
	    sizeof(sin.sin_addr));
	sin.sin_port = sin6->sin6_port;

	ai->ai_family = AF_INET;
#if defined(HAVE_STRUCT_SOCKADDR_IN_SIN_LEN)
	sin.sin_len = len;
#endif
	memcpy(ai->ai_addr, &sin, len);
	ai->ai_addrlen = len;
#endif
}