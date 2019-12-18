#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32 ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  nic_rule_action ;
struct TYPE_3__ {int match_type; int prefixlen; int /*<<< orphan*/  action; int /*<<< orphan*/  if_name; int /*<<< orphan*/  addr; struct TYPE_3__* next; } ;
typedef  TYPE_1__ nic_rule ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_DROP ; 
 int /*<<< orphan*/  ACTION_IGNORE ; 
 int /*<<< orphan*/  ACTION_LISTEN ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  FNM_CASEFOLD ; 
 int INT_LOOPBACK ; 
 int /*<<< orphan*/  IS_IPV4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_IPV6 (int /*<<< orphan*/ *) ; 
#define  MATCH_ALL 133 
#define  MATCH_IFADDR 132 
#define  MATCH_IFNAME 131 
#define  MATCH_IPV4 130 
#define  MATCH_IPV6 129 
#define  MATCH_WILDCARD 128 
 int /*<<< orphan*/  SOCK_EQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  action_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_eqprefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int is_wildcard_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listen_to_virtual_ips ; 
 TYPE_1__* nic_rule_list ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static nic_rule_action
interface_action(
	char *		if_name,
	sockaddr_u *	if_addr,
	u_int32		if_flags
	)
{
	nic_rule *	rule;
	int		isloopback;
	int		iswildcard;

	DPRINTF(4, ("interface_action: interface %s ",
		    (if_name != NULL) ? if_name : "wildcard"));

	iswildcard = is_wildcard_addr(if_addr);
	isloopback = !!(INT_LOOPBACK & if_flags);

	/*
	 * Find any matching NIC rule from --interface / -I or ntp.conf
	 * interface/nic rules.
	 */
	for (rule = nic_rule_list; rule != NULL; rule = rule->next) {

		switch (rule->match_type) {

		case MATCH_ALL:
			/* loopback and wildcard excluded from "all" */
			if (isloopback || iswildcard)
				break;
			DPRINTF(4, ("nic all %s\n",
			    action_text(rule->action)));
			return rule->action;

		case MATCH_IPV4:
			if (IS_IPV4(if_addr)) {
				DPRINTF(4, ("nic ipv4 %s\n",
				    action_text(rule->action)));
				return rule->action;
			}
			break;

		case MATCH_IPV6:
			if (IS_IPV6(if_addr)) {
				DPRINTF(4, ("nic ipv6 %s\n",
				    action_text(rule->action)));
				return rule->action;
			}
			break;

		case MATCH_WILDCARD:
			if (iswildcard) {
				DPRINTF(4, ("nic wildcard %s\n",
				    action_text(rule->action)));
				return rule->action;
			}
			break;

		case MATCH_IFADDR:
			if (rule->prefixlen != -1) {
				if (addr_eqprefix(if_addr, &rule->addr,
						  rule->prefixlen)) {

					DPRINTF(4, ("subnet address match - %s\n",
					    action_text(rule->action)));
					return rule->action;
				}
			} else
				if (SOCK_EQ(if_addr, &rule->addr)) {

					DPRINTF(4, ("address match - %s\n",
					    action_text(rule->action)));
					return rule->action;
				}
			break;

		case MATCH_IFNAME:
			if (if_name != NULL
#if defined(HAVE_FNMATCH) && defined(FNM_CASEFOLD)
			    && !fnmatch(rule->if_name, if_name, FNM_CASEFOLD)
#else
			    && !strcasecmp(if_name, rule->if_name)
#endif
			    ) {

				DPRINTF(4, ("interface name match - %s\n",
				    action_text(rule->action)));
				return rule->action;
			}
			break;
		}
	}

	/*
	 * Unless explicitly disabled such as with "nic ignore ::1"
	 * listen on loopback addresses.  Since ntpq and ntpdc query
	 * "localhost" by default, which typically resolves to ::1 and
	 * 127.0.0.1, it's useful to default to listening on both.
	 */
	if (isloopback) {
		DPRINTF(4, ("default loopback listen\n"));
		return ACTION_LISTEN;
	}

	/*
	 * Treat wildcard addresses specially.  If there is no explicit
	 * "nic ... wildcard" or "nic ... 0.0.0.0" or "nic ... ::" rule
	 * default to drop.
	 */
	if (iswildcard) {
		DPRINTF(4, ("default wildcard drop\n"));
		return ACTION_DROP;
	}

	/*
	 * Check for "virtual IP" (colon in the interface name) after
	 * the rules so that "ntpd --interface eth0:1 -novirtualips"
	 * does indeed listen on eth0:1's addresses.
	 */
	if (!listen_to_virtual_ips && if_name != NULL
	    && (strchr(if_name, ':') != NULL)) {

		DPRINTF(4, ("virtual ip - ignore\n"));
		return ACTION_IGNORE;
	}

	/*
	 * If there are no --interface/-I command-line options and no
	 * interface/nic rules in ntp.conf, the default action is to
	 * listen.  In the presence of rules from either, the default
	 * is to ignore.  This implements ntpd's traditional listen-
	 * every default with no interface listen configuration, and
	 * ensures a single -I eth0 or "nic listen eth0" means do not
	 * listen on any other addresses.
	 */
	if (NULL == nic_rule_list) {
		DPRINTF(4, ("default listen\n"));
		return ACTION_LISTEN;
	}

	DPRINTF(4, ("implicit ignore\n"));
	return ACTION_IGNORE;
}