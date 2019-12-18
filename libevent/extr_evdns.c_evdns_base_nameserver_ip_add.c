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
struct sockaddr {int dummy; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int evdns_nameserver_add_impl_ (struct evdns_base*,struct sockaddr*,int) ; 
 scalar_t__ evutil_parse_sockaddr_port (char const*,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ sockaddr_getport (struct sockaddr*) ; 
 int /*<<< orphan*/  sockaddr_setport (struct sockaddr*,int) ; 

int
evdns_base_nameserver_ip_add(struct evdns_base *base, const char *ip_as_string) {
	struct sockaddr_storage ss;
	struct sockaddr *sa;
	int len = sizeof(ss);
	int res;
	if (evutil_parse_sockaddr_port(ip_as_string, (struct sockaddr *)&ss,
		&len)) {
		log(EVDNS_LOG_WARN, "Unable to parse nameserver address %s",
			ip_as_string);
		return 4;
	}
	sa = (struct sockaddr *) &ss;
	if (sockaddr_getport(sa) == 0)
		sockaddr_setport(sa, 53);

	EVDNS_LOCK(base);
	res = evdns_nameserver_add_impl_(base, sa, len);
	EVDNS_UNLOCK(base);
	return res;
}