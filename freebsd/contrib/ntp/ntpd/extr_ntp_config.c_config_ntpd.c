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
struct addrinfo {int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  config_tree ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  INITIAL_DNS_RETRY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 int /*<<< orphan*/  clamp_systime () ; 
 int /*<<< orphan*/  config_access (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_auth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_fudge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_logconfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_mdnstries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_monitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_nic_rules (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  config_other_modes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_peers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_phone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_reset_counters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_rlimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_setvar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_system_opts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_tinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_tos (int /*<<< orphan*/ *) ; 
 scalar_t__ config_tos_clock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_trap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_ttl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_unpeers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_vars (int /*<<< orphan*/ *) ; 
 int debug ; 
 int /*<<< orphan*/  dump_restricts () ; 
 int /*<<< orphan*/  gai_test_callback ; 
 int /*<<< orphan*/  getaddrinfo_sometime (char*,char*,struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  io_open_sockets () ; 

__attribute__((used)) static void
config_ntpd(
	config_tree *ptree,
	int/*BOOL*/ input_from_files
	)
{
	/* [Bug 3435] check and esure clock sanity if configured from
	 * file and clock sanity parameters (-> basedate) are given. Do
	 * this ASAP, so we don't disturb the closed loop controller.
	 */
	if (input_from_files) {
		if (config_tos_clock(ptree))
			clamp_systime();
	}

	config_nic_rules(ptree, input_from_files);
	config_monitor(ptree);
	config_auth(ptree);
	config_tos(ptree);
	config_access(ptree);
	config_tinker(ptree);
	config_rlimit(ptree);
	config_system_opts(ptree);
	config_logconfig(ptree);
	config_phone(ptree);
	config_mdnstries(ptree);
	config_setvar(ptree);
	config_ttl(ptree);
	config_vars(ptree);

	io_open_sockets();	/* [bug 2837] dep. on config_vars() */

	config_trap(ptree);	/* [bug 2923] dep. on io_open_sockets() */
	config_other_modes(ptree);
	config_peers(ptree);
	config_unpeers(ptree);
	config_fudge(ptree);
	config_reset_counters(ptree);

#ifdef DEBUG
	if (debug > 1) {
		dump_restricts();
	}
#endif

#ifdef TEST_BLOCKING_WORKER
	{
		struct addrinfo hints;

		ZERO(hints);
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		getaddrinfo_sometime("www.cnn.com", "ntp", &hints,
				     INITIAL_DNS_RETRY,
				     gai_test_callback, (void *)1);
		hints.ai_family = AF_INET6;
		getaddrinfo_sometime("ipv6.google.com", "ntp", &hints,
				     INITIAL_DNS_RETRY,
				     gai_test_callback, (void *)0x600);
	}
#endif
}