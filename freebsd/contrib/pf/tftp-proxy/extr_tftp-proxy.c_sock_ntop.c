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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int NTOP_BUFS ; 
 char const* inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 char** ntop_buf ; 

const char *
sock_ntop(struct sockaddr *sa)
{
	static int n = 0;

	/* Cycle to next buffer. */
	n = (n + 1) % NTOP_BUFS;
	ntop_buf[n][0] = '\0';

	if (sa->sa_family == AF_INET) {
		struct sockaddr_in *sin = (struct sockaddr_in *)sa;

		return (inet_ntop(AF_INET, &sin->sin_addr, ntop_buf[n],
		    sizeof ntop_buf[0]));
	}

	if (sa->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

		return (inet_ntop(AF_INET6, &sin6->sin6_addr, ntop_buf[n],
		    sizeof ntop_buf[0]));
	}

	return (NULL);
}