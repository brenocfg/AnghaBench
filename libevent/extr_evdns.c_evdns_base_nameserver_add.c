#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int evdns_nameserver_add_impl_ (struct evdns_base*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

int
evdns_base_nameserver_add(struct evdns_base *base, unsigned long int address)
{
	struct sockaddr_in sin;
	int res;
	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.s_addr = address;
	sin.sin_port = htons(53);
	sin.sin_family = AF_INET;
	EVDNS_LOCK(base);
	res = evdns_nameserver_add_impl_(base, (struct sockaddr*)&sin, sizeof(sin));
	EVDNS_UNLOCK(base);
	return res;
}