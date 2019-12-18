#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {char* if_name; int match_class; int action; struct TYPE_5__* link; } ;
typedef  TYPE_1__ nic_rule_node ;
typedef  int /*<<< orphan*/  nic_rule_match ;
typedef  int /*<<< orphan*/  nic_rule_action ;
struct TYPE_6__ {int /*<<< orphan*/  nic_rules; } ;
typedef  TYPE_2__ config_tree ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_DROP ; 
 int /*<<< orphan*/  ACTION_IGNORE ; 
 int /*<<< orphan*/  ACTION_LISTEN ; 
 int /*<<< orphan*/  AF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ HAVE_OPT (int /*<<< orphan*/ ) ; 
 TYPE_1__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERFACE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MATCH_ALL ; 
 int /*<<< orphan*/  MATCH_IFADDR ; 
 int /*<<< orphan*/  MATCH_IFNAME ; 
 int /*<<< orphan*/  MATCH_IPV4 ; 
 int /*<<< orphan*/  MATCH_IPV6 ; 
 int /*<<< orphan*/  MATCH_WILDCARD ; 
 int /*<<< orphan*/  NOVIRTUALIPS ; 
 int SIZEOF_INADDR (int /*<<< orphan*/ ) ; 
#define  T_All 134 
#define  T_Drop 133 
#define  T_Ignore 132 
#define  T_Ipv4 131 
#define  T_Ipv6 130 
#define  T_Listen 129 
#define  T_Wildcard 128 
 int /*<<< orphan*/  add_nic_rule (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ current_time ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal_error (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_ip_address (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char*) ; 
 int sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  timer_interfacetimeout (scalar_t__) ; 

__attribute__((used)) static void
config_nic_rules(
	config_tree *ptree,
	int/*BOOL*/ input_from_file
	)
{
	nic_rule_node *	curr_node;
	sockaddr_u	addr;
	nic_rule_match	match_type;
	nic_rule_action	action;
	char *		if_name;
	char *		pchSlash;
	int		prefixlen;
	int		addrbits;

	curr_node = HEAD_PFIFO(ptree->nic_rules);

	if (curr_node != NULL
	    && (HAVE_OPT( NOVIRTUALIPS ) || HAVE_OPT( INTERFACE ))) {
		msyslog(LOG_ERR,
			"interface/nic rules are not allowed with --interface (-I) or --novirtualips (-L)%s",
			(input_from_file) ? ", exiting" : "");
		if (input_from_file)
			exit(1);
		else
			return;
	}

	for (; curr_node != NULL; curr_node = curr_node->link) {
		prefixlen = -1;
		if_name = curr_node->if_name;
		if (if_name != NULL)
			if_name = estrdup(if_name);

		switch (curr_node->match_class) {

		default:
			fatal_error("config_nic_rules: match-class-token=%d", curr_node->match_class);

		case 0:
			/*
			 * 0 is out of range for valid token T_...
			 * and in a nic_rules_node indicates the
			 * interface descriptor is either a name or
			 * address, stored in if_name in either case.
			 */
			INSIST(if_name != NULL);
			pchSlash = strchr(if_name, '/');
			if (pchSlash != NULL)
				*pchSlash = '\0';
			if (is_ip_address(if_name, AF_UNSPEC, &addr)) {
				match_type = MATCH_IFADDR;
				if (pchSlash != NULL
				    && 1 == sscanf(pchSlash + 1, "%d",
					    &prefixlen)) {
					addrbits = 8 *
					    SIZEOF_INADDR(AF(&addr));
					prefixlen = max(-1, prefixlen);
					prefixlen = min(prefixlen,
							addrbits);
				}
			} else {
				match_type = MATCH_IFNAME;
				if (pchSlash != NULL)
					*pchSlash = '/';
			}
			break;

		case T_All:
			match_type = MATCH_ALL;
			break;

		case T_Ipv4:
			match_type = MATCH_IPV4;
			break;

		case T_Ipv6:
			match_type = MATCH_IPV6;
			break;

		case T_Wildcard:
			match_type = MATCH_WILDCARD;
			break;
		}

		switch (curr_node->action) {

		default:
			fatal_error("config_nic_rules: action-token=%d", curr_node->action);

		case T_Listen:
			action = ACTION_LISTEN;
			break;

		case T_Ignore:
			action = ACTION_IGNORE;
			break;

		case T_Drop:
			action = ACTION_DROP;
			break;
		}

		add_nic_rule(match_type, if_name, prefixlen,
			     action);
		timer_interfacetimeout(current_time + 2);
		if (if_name != NULL)
			free(if_name);
	}
}