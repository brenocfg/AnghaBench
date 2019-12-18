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
 scalar_t__ evdns_base_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int evdns_base_resolv_conf_parse (scalar_t__,int,char const* const) ; 

int
evdns_resolv_conf_parse(int flags, const char *const filename) {
	if (!current_base)
		current_base = evdns_base_new(NULL, 0);
	return evdns_base_resolv_conf_parse(current_base, flags, filename);
}