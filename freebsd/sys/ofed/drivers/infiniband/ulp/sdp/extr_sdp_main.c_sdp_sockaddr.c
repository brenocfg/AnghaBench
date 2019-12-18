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
struct in_addr {int dummy; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; struct in_addr sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  M_SONAME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct sockaddr_in* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sockaddr *
sdp_sockaddr(in_port_t port, struct in_addr *addr_p)
{
	struct sockaddr_in *sin;

	sin = malloc(sizeof *sin, M_SONAME,
		M_WAITOK | M_ZERO);
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	sin->sin_addr = *addr_p;
	sin->sin_port = port;

	return (struct sockaddr *)sin;
}