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
typedef  int u_int32_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct in6_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  ipv6 ;
typedef  int /*<<< orphan*/  in_addr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  AU_IPv4 129 
#define  AU_IPv6 128 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  bcopy (int*,struct in_addr*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 

__attribute__((used)) static void
print_ip_ex_address(FILE *fp, u_int32_t type, u_int32_t *ipaddr)
{
	struct in_addr ipv4;
	struct in6_addr ipv6;
	char dst[INET6_ADDRSTRLEN];

	switch (type) {
	case AU_IPv4:
		ipv4.s_addr = (in_addr_t)(ipaddr[0]);
		fprintf(fp, "%s", inet_ntop(AF_INET, &ipv4, dst,
		    INET6_ADDRSTRLEN));
		break;

	case AU_IPv6:
		bcopy(ipaddr, &ipv6, sizeof(ipv6));
		fprintf(fp, "%s", inet_ntop(AF_INET6, &ipv6, dst,
		    INET6_ADDRSTRLEN));
		break;

	default:
		fprintf(fp, "invalid");
	}
}