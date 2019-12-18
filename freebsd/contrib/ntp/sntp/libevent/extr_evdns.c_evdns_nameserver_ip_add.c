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
 scalar_t__ current_base ; 
 int evdns_base_nameserver_ip_add (scalar_t__,char const*) ; 
 scalar_t__ evdns_base_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
evdns_nameserver_ip_add(const char *ip_as_string) {
	if (!current_base)
		current_base = evdns_base_new(NULL, 0);
	return evdns_base_nameserver_ip_add(current_base, ip_as_string);
}