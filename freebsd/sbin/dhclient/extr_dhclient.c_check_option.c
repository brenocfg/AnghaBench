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
struct client_lease {TYPE_1__* options; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  DHO_ALL_SUBNETS_LOCAL 206 
#define  DHO_ARP_CACHE_TIMEOUT 205 
#define  DHO_BOOTFILE_NAME 204 
#define  DHO_BOOT_SIZE 203 
#define  DHO_BROADCAST_ADDRESS 202 
#define  DHO_CLASSLESS_ROUTES 201 
#define  DHO_COOKIE_SERVERS 200 
#define  DHO_DEFAULT_IP_TTL 199 
#define  DHO_DEFAULT_TCP_TTL 198 
#define  DHO_DHCP_CLASS_IDENTIFIER 197 
#define  DHO_DHCP_CLIENT_IDENTIFIER 196 
#define  DHO_DHCP_LEASE_TIME 195 
#define  DHO_DHCP_MAX_MESSAGE_SIZE 194 
#define  DHO_DHCP_MESSAGE 193 
#define  DHO_DHCP_MESSAGE_TYPE 192 
#define  DHO_DHCP_OPTION_OVERLOAD 191 
#define  DHO_DHCP_PARAMETER_REQUEST_LIST 190 
#define  DHO_DHCP_REBINDING_TIME 189 
#define  DHO_DHCP_RENEWAL_TIME 188 
#define  DHO_DHCP_REQUESTED_ADDRESS 187 
#define  DHO_DHCP_SERVER_IDENTIFIER 186 
#define  DHO_DHCP_USER_CLASS_ID 185 
#define  DHO_DOMAIN_NAME 184 
#define  DHO_DOMAIN_NAME_SERVERS 183 
#define  DHO_DOMAIN_SEARCH 182 
#define  DHO_END 181 
#define  DHO_EXTENSIONS_PATH 180 
#define  DHO_FINGER_SERVER 179 
#define  DHO_FONT_SERVERS 178 
#define  DHO_HOST_NAME 177 
#define  DHO_IEEE802_3_ENCAPSULATION 176 
#define  DHO_IMPRESS_SERVERS 175 
#define  DHO_INTERFACE_MTU 174 
#define  DHO_IP_FORWARDING 173 
#define  DHO_IRC_SERVER 172 
#define  DHO_LOG_SERVERS 171 
#define  DHO_LPR_SERVERS 170 
#define  DHO_MASK_SUPPLIER 169 
#define  DHO_MAX_DGRAM_REASSEMBLY 168 
#define  DHO_MERIT_DUMP 167 
#define  DHO_MOBILE_IP_HOME_AGENT 166 
#define  DHO_NAME_SERVERS 165 
#define  DHO_NETBIOS_DD_SERVER 164 
#define  DHO_NETBIOS_NAME_SERVERS 163 
#define  DHO_NETBIOS_NODE_TYPE 162 
#define  DHO_NETBIOS_SCOPE 161 
#define  DHO_NISPLUS_DOMAIN 160 
#define  DHO_NISPLUS_SERVERS 159 
#define  DHO_NIS_DOMAIN 158 
#define  DHO_NIS_SERVERS 157 
#define  DHO_NNTP_SERVER 156 
#define  DHO_NON_LOCAL_SOURCE_ROUTING 155 
#define  DHO_NTP_SERVERS 154 
#define  DHO_PAD 153 
#define  DHO_PATH_MTU_AGING_TIMEOUT 152 
#define  DHO_PATH_MTU_PLATEAU_TABLE 151 
#define  DHO_PERFORM_MASK_DISCOVERY 150 
#define  DHO_POLICY_FILTER 149 
#define  DHO_POP_SERVER 148 
#define  DHO_RESOURCE_LOCATION_SERVERS 147 
#define  DHO_ROOT_PATH 146 
#define  DHO_ROUTERS 145 
#define  DHO_ROUTER_DISCOVERY 144 
#define  DHO_ROUTER_SOLICITATION_ADDRESS 143 
#define  DHO_SMTP_SERVER 142 
#define  DHO_STATIC_ROUTES 141 
#define  DHO_STREETTALK_DA_SERVER 140 
#define  DHO_STREETTALK_SERVER 139 
#define  DHO_SUBNET_MASK 138 
#define  DHO_SWAP_SERVER 137 
#define  DHO_TCP_KEEPALIVE_GARBAGE 136 
#define  DHO_TCP_KEEPALIVE_INTERVAL 135 
#define  DHO_TFTP_SERVER_NAME 134 
#define  DHO_TIME_OFFSET 133 
#define  DHO_TIME_SERVERS 132 
#define  DHO_TRAILER_ENCAPSULATION 131 
#define  DHO_VENDOR_ENCAPSULATED_OPTIONS 130 
#define  DHO_WWW_SERVER 129 
#define  DHO_X_DISPLAY_MANAGER 128 
 int check_classless_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_search (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4addrs (char const*) ; 
 char* option_as_string (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pretty_print_option (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_hnok (char const*) ; 
 int unknown_ok ; 
 int /*<<< orphan*/  warning (char*,...) ; 

int
check_option(struct client_lease *l, int option)
{
	const char *opbuf;
	const char *sbuf;

	/* we use this, since this is what gets passed to dhclient-script */

	opbuf = pretty_print_option(option, l->options[option].data,
	    l->options[option].len, 0, 0);

	sbuf = option_as_string(option, l->options[option].data,
	    l->options[option].len);

	switch (option) {
	case DHO_SUBNET_MASK:
	case DHO_TIME_SERVERS:
	case DHO_NAME_SERVERS:
	case DHO_ROUTERS:
	case DHO_DOMAIN_NAME_SERVERS:
	case DHO_LOG_SERVERS:
	case DHO_COOKIE_SERVERS:
	case DHO_LPR_SERVERS:
	case DHO_IMPRESS_SERVERS:
	case DHO_RESOURCE_LOCATION_SERVERS:
	case DHO_SWAP_SERVER:
	case DHO_BROADCAST_ADDRESS:
	case DHO_NIS_SERVERS:
	case DHO_NTP_SERVERS:
	case DHO_NETBIOS_NAME_SERVERS:
	case DHO_NETBIOS_DD_SERVER:
	case DHO_FONT_SERVERS:
	case DHO_DHCP_SERVER_IDENTIFIER:
	case DHO_NISPLUS_SERVERS:
	case DHO_MOBILE_IP_HOME_AGENT:
	case DHO_SMTP_SERVER:
	case DHO_POP_SERVER:
	case DHO_NNTP_SERVER:
	case DHO_WWW_SERVER:
	case DHO_FINGER_SERVER:
	case DHO_IRC_SERVER:
	case DHO_STREETTALK_SERVER:
	case DHO_STREETTALK_DA_SERVER:
		if (!ipv4addrs(opbuf)) {
			warning("Invalid IP address in option: %s", opbuf);
			return (0);
		}
		return (1)  ;
	case DHO_HOST_NAME:
	case DHO_NIS_DOMAIN:
	case DHO_NISPLUS_DOMAIN:
	case DHO_TFTP_SERVER_NAME:
		if (!res_hnok(sbuf)) {
			warning("Bogus Host Name option %d: %s (%s)", option,
			    sbuf, opbuf);
			l->options[option].len = 0;
			free(l->options[option].data);
		}
		return (1);
	case DHO_DOMAIN_NAME:
	case DHO_DOMAIN_SEARCH:
		if (!res_hnok(sbuf)) {
			if (!check_search(sbuf)) {
				warning("Bogus domain search list %d: %s (%s)",
				    option, sbuf, opbuf);
				l->options[option].len = 0;
				free(l->options[option].data);
			}
		}
		return (1);
	case DHO_PAD:
	case DHO_TIME_OFFSET:
	case DHO_BOOT_SIZE:
	case DHO_MERIT_DUMP:
	case DHO_ROOT_PATH:
	case DHO_EXTENSIONS_PATH:
	case DHO_IP_FORWARDING:
	case DHO_NON_LOCAL_SOURCE_ROUTING:
	case DHO_POLICY_FILTER:
	case DHO_MAX_DGRAM_REASSEMBLY:
	case DHO_DEFAULT_IP_TTL:
	case DHO_PATH_MTU_AGING_TIMEOUT:
	case DHO_PATH_MTU_PLATEAU_TABLE:
	case DHO_INTERFACE_MTU:
	case DHO_ALL_SUBNETS_LOCAL:
	case DHO_PERFORM_MASK_DISCOVERY:
	case DHO_MASK_SUPPLIER:
	case DHO_ROUTER_DISCOVERY:
	case DHO_ROUTER_SOLICITATION_ADDRESS:
	case DHO_STATIC_ROUTES:
	case DHO_TRAILER_ENCAPSULATION:
	case DHO_ARP_CACHE_TIMEOUT:
	case DHO_IEEE802_3_ENCAPSULATION:
	case DHO_DEFAULT_TCP_TTL:
	case DHO_TCP_KEEPALIVE_INTERVAL:
	case DHO_TCP_KEEPALIVE_GARBAGE:
	case DHO_VENDOR_ENCAPSULATED_OPTIONS:
	case DHO_NETBIOS_NODE_TYPE:
	case DHO_NETBIOS_SCOPE:
	case DHO_X_DISPLAY_MANAGER:
	case DHO_DHCP_REQUESTED_ADDRESS:
	case DHO_DHCP_LEASE_TIME:
	case DHO_DHCP_OPTION_OVERLOAD:
	case DHO_DHCP_MESSAGE_TYPE:
	case DHO_DHCP_PARAMETER_REQUEST_LIST:
	case DHO_DHCP_MESSAGE:
	case DHO_DHCP_MAX_MESSAGE_SIZE:
	case DHO_DHCP_RENEWAL_TIME:
	case DHO_DHCP_REBINDING_TIME:
	case DHO_DHCP_CLASS_IDENTIFIER:
	case DHO_DHCP_CLIENT_IDENTIFIER:
	case DHO_BOOTFILE_NAME:
	case DHO_DHCP_USER_CLASS_ID:
	case DHO_END:
		return (1);
	case DHO_CLASSLESS_ROUTES:
		return (check_classless_option(l->options[option].data,
		    l->options[option].len));
	default:
		warning("unknown dhcp option value 0x%x", option);
		return (unknown_ok);
	}
}