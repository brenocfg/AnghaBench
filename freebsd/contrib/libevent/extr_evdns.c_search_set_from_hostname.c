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
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  HOST_NAME_MAX ; 
 scalar_t__ gethostname (char*,int) ; 
 int /*<<< orphan*/  search_postfix_add (struct evdns_base*,char*) ; 
 int /*<<< orphan*/  search_postfix_clear (struct evdns_base*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
search_set_from_hostname(struct evdns_base *base) {
	char hostname[HOST_NAME_MAX + 1], *domainname;

	ASSERT_LOCKED(base);
	search_postfix_clear(base);
	if (gethostname(hostname, sizeof(hostname))) return;
	domainname = strchr(hostname, '.');
	if (!domainname) return;
	search_postfix_add(base, domainname);
}