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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; scalar_t__ sin_family; } ;
typedef  scalar_t__ socklen_t ;
typedef  enum verbosity_value { ____Placeholder_verbosity_value } verbosity_value ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ inet_ntop (int,void*,char*,scalar_t__) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  verbose (int,char*,char const*,char*,char const*,char*,int,...) ; 
 int verbosity ; 

void log_name_addr(enum verbosity_value v, const char* str, uint8_t* zone, 
	struct sockaddr_storage* addr, socklen_t addrlen)
{
	uint16_t port;
	const char* family = "unknown_family ";
	char namebuf[LDNS_MAX_DOMAINLEN+1];
	char dest[100];
	int af = (int)((struct sockaddr_in*)addr)->sin_family;
	void* sinaddr = &((struct sockaddr_in*)addr)->sin_addr;
	if(verbosity < v)
		return;
	switch(af) {
		case AF_INET: family=""; break;
		case AF_INET6: family="";
			sinaddr = &((struct sockaddr_in6*)addr)->sin6_addr;
			break;
		case AF_LOCAL: family="local "; break;
		default: break;
	}
	if(inet_ntop(af, sinaddr, dest, (socklen_t)sizeof(dest)) == 0) {
		(void)strlcpy(dest, "(inet_ntop error)", sizeof(dest));
	}
	dest[sizeof(dest)-1] = 0;
	port = ntohs(((struct sockaddr_in*)addr)->sin_port);
	dname_str(zone, namebuf);
	if(af != AF_INET && af != AF_INET6)
		verbose(v, "%s <%s> %s%s#%d (addrlen %d)",
			str, namebuf, family, dest, (int)port, (int)addrlen);
	else	verbose(v, "%s <%s> %s%s#%d",
			str, namebuf, family, dest, (int)port);
}