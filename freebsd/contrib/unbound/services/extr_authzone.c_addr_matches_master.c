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
struct auth_master {int /*<<< orphan*/  host; int /*<<< orphan*/  http; scalar_t__ allow_notify; int /*<<< orphan*/  list; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int addr_in_common (struct sockaddr_storage*,int,struct sockaddr_storage*,int,scalar_t__) ; 
 scalar_t__ addr_in_list (int /*<<< orphan*/ ,struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ extstrtoaddr (int /*<<< orphan*/ ,struct sockaddr_storage*,scalar_t__*) ; 
 scalar_t__ netblockstrtoaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_storage*,scalar_t__*,int*) ; 
 scalar_t__ sockaddr_cmp_addr (struct sockaddr_storage*,scalar_t__,struct sockaddr_storage*,scalar_t__) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int
addr_matches_master(struct auth_master* master, struct sockaddr_storage* addr,
	socklen_t addrlen, struct auth_master** fromhost)
{
	struct sockaddr_storage a;
	socklen_t alen = 0;
	int net = 0;
	if(addr_in_list(master->list, addr, addrlen)) {
		*fromhost = master;
		return 1;	
	}
	/* compare address (but not port number, that is the destination
	 * port of the master, the port number of the received notify is
	 * allowed to by any port on that master) */
	if(extstrtoaddr(master->host, &a, &alen) &&
		sockaddr_cmp_addr(addr, addrlen, &a, alen)==0) {
		*fromhost = master;
		return 1;
	}
	/* prefixes, addr/len, like 10.0.0.0/8 */
	/* not http and has a / and there is one / */
	if(master->allow_notify && !master->http &&
		strchr(master->host, '/') != NULL &&
		strchr(master->host, '/') == strrchr(master->host, '/') &&
		netblockstrtoaddr(master->host, UNBOUND_DNS_PORT, &a, &alen,
		&net) && alen == addrlen) {
		if(addr_in_common(addr, (addr_is_ip6(addr, addrlen)?128:32),
			&a, net, alen) >= net) {
			*fromhost = NULL; /* prefix does not have destination
				to send the probe or transfer with */
			return 1; /* matches the netblock */
		}
	}
	return 0;
}