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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

uint16_t
key_portfromsaddr(struct sockaddr *sa)
{

	switch (sa->sa_family) {
#ifdef INET
	case AF_INET:
		return ((struct sockaddr_in *)sa)->sin_port;
#endif
#ifdef INET6
	case AF_INET6:
		return ((struct sockaddr_in6 *)sa)->sin6_port;
#endif
	}
	return (0);
}