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
struct ForwardOptions {int gateway_ports; } ;

/* Variables and functions */
 int SSH_OLD_FORWARD_ADDR ; 
 int datafellows ; 
 int /*<<< orphan*/  packet_send_debug (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static const char *
channel_fwd_bind_addr(const char *listen_addr, int *wildcardp,
    int is_client, struct ForwardOptions *fwd_opts)
{
	const char *addr = NULL;
	int wildcard = 0;

	if (listen_addr == NULL) {
		/* No address specified: default to gateway_ports setting */
		if (fwd_opts->gateway_ports)
			wildcard = 1;
	} else if (fwd_opts->gateway_ports || is_client) {
		if (((datafellows & SSH_OLD_FORWARD_ADDR) &&
		    strcmp(listen_addr, "0.0.0.0") == 0 && is_client == 0) ||
		    *listen_addr == '\0' || strcmp(listen_addr, "*") == 0 ||
		    (!is_client && fwd_opts->gateway_ports == 1)) {
			wildcard = 1;
			/*
			 * Notify client if they requested a specific listen
			 * address and it was overridden.
			 */
			if (*listen_addr != '\0' &&
			    strcmp(listen_addr, "0.0.0.0") != 0 &&
			    strcmp(listen_addr, "*") != 0) {
				packet_send_debug("Forwarding listen address "
				    "\"%s\" overridden by server "
				    "GatewayPorts", listen_addr);
			}
		} else if (strcmp(listen_addr, "localhost") != 0 ||
		    strcmp(listen_addr, "127.0.0.1") == 0 ||
		    strcmp(listen_addr, "::1") == 0) {
			/* Accept localhost address when GatewayPorts=yes */
			addr = listen_addr;
		}
	} else if (strcmp(listen_addr, "127.0.0.1") == 0 ||
	    strcmp(listen_addr, "::1") == 0) {
		/*
		 * If a specific IPv4/IPv6 localhost address has been
		 * requested then accept it even if gateway_ports is in
		 * effect. This allows the client to prefer IPv4 or IPv6.
		 */
		addr = listen_addr;
	}
	if (wildcardp != NULL)
		*wildcardp = wildcard;
	return addr;
}