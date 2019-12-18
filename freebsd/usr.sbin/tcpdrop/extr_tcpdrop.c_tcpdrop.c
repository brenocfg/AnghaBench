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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct host_service {char* hs_host; char* hs_service; } ;

/* Variables and functions */
 size_t TCPDROP_FOREIGN ; 
 size_t TCPDROP_LOCAL ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  sockinfo (struct sockaddr const*,struct host_service*) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr_storage**,int) ; 
 scalar_t__ tcpdrop_list_commands ; 
 int /*<<< orphan*/  warn (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static bool
tcpdrop(const struct sockaddr *lsa, const struct sockaddr *fsa)
{
	struct host_service local, foreign;
	struct sockaddr_storage addrs[2];
	int rv;

	memcpy(&addrs[TCPDROP_FOREIGN], fsa, fsa->sa_len);
	memcpy(&addrs[TCPDROP_LOCAL], lsa, lsa->sa_len);

	sockinfo(lsa, &local);
	sockinfo(fsa, &foreign);

	if (tcpdrop_list_commands) {
		printf("tcpdrop %s %s %s %s\n", local.hs_host, local.hs_service,
		    foreign.hs_host, foreign.hs_service);
		return (true);
	}

	rv = sysctlbyname("net.inet.tcp.drop", NULL, NULL, &addrs,
	    sizeof addrs);
	if (rv == -1) {
		warn("%s %s %s %s", local.hs_host, local.hs_service,
		    foreign.hs_host, foreign.hs_service);
		return (false);
	}
	printf("%s %s %s %s: dropped\n", local.hs_host, local.hs_service,
	    foreign.hs_host, foreign.hs_service);
	return (true);
}