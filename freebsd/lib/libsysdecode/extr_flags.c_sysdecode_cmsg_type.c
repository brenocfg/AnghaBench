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
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPPROTO_SCTP ; 
 int SOL_SOCKET ; 
 int /*<<< orphan*/  cmsgtypeip ; 
 int /*<<< orphan*/  cmsgtypeipv6 ; 
 int /*<<< orphan*/  cmsgtypesctp ; 
 int /*<<< orphan*/  cmsgtypesocket ; 
 char const* lookup_value (int /*<<< orphan*/ ,int) ; 

const char *
sysdecode_cmsg_type(int cmsg_level, int cmsg_type)
{

	if (cmsg_level == SOL_SOCKET)
		return (lookup_value(cmsgtypesocket, cmsg_type));
	if (cmsg_level == IPPROTO_IP)
		return (lookup_value(cmsgtypeip, cmsg_type));
	if (cmsg_level == IPPROTO_IPV6)
		return (lookup_value(cmsgtypeipv6, cmsg_type));
	if (cmsg_level == IPPROTO_SCTP)
		return (lookup_value(cmsgtypesctp, cmsg_type));
	return (NULL);
}