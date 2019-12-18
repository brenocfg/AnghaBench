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
typedef  int /*<<< orphan*/  u_int32_t ;
struct addrinfo {int ai_family; void* ai_flags; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 void* AI_NUMERICHOST ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int inet_pton (int const,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setbindhost(struct addrinfo **ai, const char *bindhost, struct addrinfo hints)
{
	int ecode;
	u_int32_t host_addr[4];  /* IPv4 or IPv6 */
	const char *hostptr;

	if (bindhost == NULL || strcmp("*", bindhost) == 0)
		hostptr = NULL;
	else
		hostptr = bindhost;

	if (hostptr != NULL) {
		switch (hints.ai_family) {
		case AF_INET:
			if (inet_pton(AF_INET, hostptr, host_addr) == 1) {
				hints.ai_flags = AI_NUMERICHOST;
			} else {
				if (inet_pton(AF_INET6, hostptr,
				    host_addr) == 1)
					return (1);
			}
			break;
		case AF_INET6:
			if (inet_pton(AF_INET6, hostptr, host_addr) == 1) {
				hints.ai_flags = AI_NUMERICHOST;
			} else {
				if (inet_pton(AF_INET, hostptr,
				    host_addr) == 1)
					return (1);
			}
			break;
		default:
			break;
		}
	}
	
	ecode = getaddrinfo(hostptr, "nfs", &hints, ai);
	if (ecode != 0) {
		syslog(LOG_ERR, "getaddrinfo %s: %s", bindhost,
		    gai_strerror(ecode));
		return (1);
	}
	return (0);
}