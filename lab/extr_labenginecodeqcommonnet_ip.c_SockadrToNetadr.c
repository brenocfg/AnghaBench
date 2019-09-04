#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  scope_id; int /*<<< orphan*/  port; int /*<<< orphan*/  ip6; int /*<<< orphan*/  type; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ netadr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NA_IP6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void SockadrToNetadr( struct sockaddr *s, netadr_t *a ) {
	if (s->sa_family == AF_INET) {
		a->type = NA_IP;
		*(int *)&a->ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
		a->port = ((struct sockaddr_in *)s)->sin_port;
	}
	else if(s->sa_family == AF_INET6)
	{
		a->type = NA_IP6;
		memcpy(a->ip6, &((struct sockaddr_in6 *)s)->sin6_addr, sizeof(a->ip6));
		a->port = ((struct sockaddr_in6 *)s)->sin6_port;
		a->scope_id = ((struct sockaddr_in6 *)s)->sin6_scope_id;
	}
}