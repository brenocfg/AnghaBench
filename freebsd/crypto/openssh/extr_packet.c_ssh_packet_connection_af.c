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
typedef  int /*<<< orphan*/  to ;
struct ssh {TYPE_1__* state; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_2__ {int /*<<< orphan*/  connection_out; } ;

/* Variables and functions */
 int AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

int
ssh_packet_connection_af(struct ssh *ssh)
{
	struct sockaddr_storage to;
	socklen_t tolen = sizeof(to);

	memset(&to, 0, sizeof(to));
	if (getsockname(ssh->state->connection_out, (struct sockaddr *)&to,
	    &tolen) < 0)
		return 0;
#ifdef IPV4_IN_IPV6
	if (to.ss_family == AF_INET6 &&
	    IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)&to)->sin6_addr))
		return AF_INET;
#endif
	return to.ss_family;
}