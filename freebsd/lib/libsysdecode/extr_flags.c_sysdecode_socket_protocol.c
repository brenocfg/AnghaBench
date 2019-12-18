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

/* Variables and functions */
#define  PF_INET 129 
#define  PF_INET6 128 
 char const* lookup_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sockipproto ; 

const char *
sysdecode_socket_protocol(int domain, int protocol)
{

	switch (domain) {
	case PF_INET:
	case PF_INET6:
		return (lookup_value(sockipproto, protocol));
	default:
		return (NULL);
	}
}