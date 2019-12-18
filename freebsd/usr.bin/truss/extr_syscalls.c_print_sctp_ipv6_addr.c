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
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 char* inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 

__attribute__((used)) static void
print_sctp_ipv6_addr(FILE *fp, struct in6_addr *addr)
{
	char buf[INET6_ADDRSTRLEN];
	const char *s;

	s = inet_ntop(AF_INET6, addr, buf, INET6_ADDRSTRLEN);
	if (s != NULL)
		fprintf(fp, "{addr=%s}", s);
	else
		fputs("{addr=???}", fp);
}