#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nic_rule_match ;
typedef  int /*<<< orphan*/  nic_rule_action ;
struct TYPE_4__ {int prefixlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  if_name; int /*<<< orphan*/  action; scalar_t__ match_type; } ;
typedef  TYPE_1__ nic_rule ;
typedef  int isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MATCH_IFADDR ; 
 scalar_t__ MATCH_IFNAME ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 TYPE_1__* emalloc_zero (int) ; 
 int /*<<< orphan*/  estrdup (char const*) ; 
 int is_ip_address (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  nic_rule_list ; 

void
add_nic_rule(
	nic_rule_match	match_type,
	const char *	if_name,	/* interface name or numeric address */
	int		prefixlen,
	nic_rule_action	action
	)
{
	nic_rule *	rule;
	isc_boolean_t	is_ip;

	rule = emalloc_zero(sizeof(*rule));
	rule->match_type = match_type;
	rule->prefixlen = prefixlen;
	rule->action = action;

	if (MATCH_IFNAME == match_type) {
		REQUIRE(NULL != if_name);
		rule->if_name = estrdup(if_name);
	} else if (MATCH_IFADDR == match_type) {
		REQUIRE(NULL != if_name);
		/* set rule->addr */
		is_ip = is_ip_address(if_name, AF_UNSPEC, &rule->addr);
		REQUIRE(is_ip);
	} else
		REQUIRE(NULL == if_name);

	LINK_SLIST(nic_rule_list, rule, next);
}