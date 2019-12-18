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
struct sockaddr_storage {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_port; scalar_t__ sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; scalar_t__ sin_family; } ;
struct sockaddr_in6 {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_port; scalar_t__ sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; scalar_t__ sin_family; } ;
struct sockaddr_in {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_port; scalar_t__ sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct sa_port_ent {scalar_t__ safamily; scalar_t__ parse; int /*<<< orphan*/  addr; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  TT_FAIL (char*) ; 
 int evutil_inet_pton (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int evutil_parse_sockaddr_port (scalar_t__,struct sockaddr*,int*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct sockaddr_storage*,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 struct sa_port_ent* sa_port_ents ; 

__attribute__((used)) static void
regress_sockaddr_port_parse(void *ptr)
{
	struct sockaddr_storage ss;
	int i, r;

	for (i = 0; sa_port_ents[i].parse; ++i) {
		struct sa_port_ent *ent = &sa_port_ents[i];
		int len = sizeof(ss);
		memset(&ss, 0, sizeof(ss));
		r = evutil_parse_sockaddr_port(ent->parse, (struct sockaddr*)&ss, &len);
		if (r < 0) {
			if (ent->safamily)
				TT_FAIL(("Couldn't parse %s!", ent->parse));
			continue;
		} else if (! ent->safamily) {
			TT_FAIL(("Shouldn't have been able to parse %s!", ent->parse));
			continue;
		}
		if (ent->safamily == AF_INET) {
			struct sockaddr_in sin;
			memset(&sin, 0, sizeof(sin));
#ifdef EVENT__HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
			sin.sin_len = sizeof(sin);
#endif
			sin.sin_family = AF_INET;
			sin.sin_port = htons(ent->port);
			r = evutil_inet_pton(AF_INET, ent->addr, &sin.sin_addr);
			if (1 != r) {
				TT_FAIL(("Couldn't parse ipv4 target %s.", ent->addr));
			} else if (memcmp(&sin, &ss, sizeof(sin))) {
				TT_FAIL(("Parse for %s was not as expected.", ent->parse));
			} else if (len != sizeof(sin)) {
				TT_FAIL(("Length for %s not as expected.",ent->parse));
			}
		} else {
			struct sockaddr_in6 sin6;
			memset(&sin6, 0, sizeof(sin6));
#ifdef EVENT__HAVE_STRUCT_SOCKADDR_IN6_SIN6_LEN
			sin6.sin6_len = sizeof(sin6);
#endif
			sin6.sin6_family = AF_INET6;
			sin6.sin6_port = htons(ent->port);
			r = evutil_inet_pton(AF_INET6, ent->addr, &sin6.sin6_addr);
			if (1 != r) {
				TT_FAIL(("Couldn't parse ipv6 target %s.", ent->addr));
			} else if (memcmp(&sin6, &ss, sizeof(sin6))) {
				TT_FAIL(("Parse for %s was not as expected.", ent->parse));
			} else if (len != sizeof(sin6)) {
				TT_FAIL(("Length for %s not as expected.",ent->parse));
			}
		}
	}
}