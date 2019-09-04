#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; struct in6_addr sin6_addr; void* sin6_family; int /*<<< orphan*/  sin6_scope_id; } ;
struct TYPE_5__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  scope_id; int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ netadr_t ;
struct TYPE_7__ {struct in6_addr ipv6mr_multiaddr; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int INADDR_BROADCAST ; 
 scalar_t__ NA_BROADCAST ; 
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IP6 ; 
 scalar_t__ NA_MULTICAST6 ; 
 TYPE_3__ curgroup ; 

__attribute__((used)) static void NetadrToSockadr( netadr_t *a, struct sockaddr *s ) {
	if( a->type == NA_BROADCAST ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_port = a->port;
		((struct sockaddr_in *)s)->sin_addr.s_addr = INADDR_BROADCAST;
	}
	else if( a->type == NA_IP ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_addr.s_addr = *(int *)&a->ip;
		((struct sockaddr_in *)s)->sin_port = a->port;
	}
	else if( a->type == NA_IP6 ) {
		((struct sockaddr_in6 *)s)->sin6_family = AF_INET6;
		((struct sockaddr_in6 *)s)->sin6_addr = * ((struct in6_addr *) &a->ip6);
		((struct sockaddr_in6 *)s)->sin6_port = a->port;
		((struct sockaddr_in6 *)s)->sin6_scope_id = a->scope_id;
	}
	else if(a->type == NA_MULTICAST6)
	{
		((struct sockaddr_in6 *)s)->sin6_family = AF_INET6;
		((struct sockaddr_in6 *)s)->sin6_addr = curgroup.ipv6mr_multiaddr;
		((struct sockaddr_in6 *)s)->sin6_port = a->port;
	}
}