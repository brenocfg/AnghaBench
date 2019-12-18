#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u_int8_t ;
typedef  int /*<<< orphan*/  tbuf ;
struct interface_info {TYPE_4__* client; } ;
struct iaddr {char* iabuf; size_t len; } ;
struct client_lease {char* filename; char* server_name; scalar_t__ expiry; TYPE_2__* options; struct iaddr address; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  dbuf ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_1__* config; } ;
struct TYPE_9__ {char* data; size_t len; } ;
struct TYPE_8__ {char* data; size_t len; } ;
struct TYPE_7__ {int* default_actions; TYPE_3__* defaults; } ;

/* Variables and functions */
#define  ACTION_APPEND 131 
#define  ACTION_DEFAULT 130 
#define  ACTION_PREPEND 129 
#define  ACTION_SUPERSEDE 128 
 size_t DHO_BROADCAST_ADDRESS ; 
 size_t DHO_SUBNET_MASK ; 
 struct iaddr broadcast_addr (struct iaddr,struct iaddr) ; 
 scalar_t__ dhcp_option_ev_name (char*,int,TYPE_5__*) ; 
 TYPE_5__* dhcp_options ; 
 struct interface_info* ifi ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* piaddr (struct iaddr) ; 
 char* pretty_print_option (int,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_set_env (TYPE_4__*,char const*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct iaddr subnet_number (struct iaddr,struct iaddr) ; 
 int /*<<< orphan*/  warning (char*,char*,int /*<<< orphan*/ ) ; 

void
priv_script_write_params(const char *prefix, struct client_lease *lease)
{
	struct interface_info *ip = ifi;
	u_int8_t dbuf[1500], *dp = NULL;
	int i;
	size_t len;
	char tbuf[128];

	script_set_env(ip->client, prefix, "ip_address",
	    piaddr(lease->address));

	if (ip->client->config->default_actions[DHO_SUBNET_MASK] ==
	    ACTION_SUPERSEDE) {
		dp = ip->client->config->defaults[DHO_SUBNET_MASK].data;
		len = ip->client->config->defaults[DHO_SUBNET_MASK].len;
	} else {
		dp = lease->options[DHO_SUBNET_MASK].data;
		len = lease->options[DHO_SUBNET_MASK].len;
	}
	if (len && (len < sizeof(lease->address.iabuf))) {
		struct iaddr netmask, subnet, broadcast;

		memcpy(netmask.iabuf, dp, len);
		netmask.len = len;
		subnet = subnet_number(lease->address, netmask);
		if (subnet.len) {
			script_set_env(ip->client, prefix, "network_number",
			    piaddr(subnet));
			if (!lease->options[DHO_BROADCAST_ADDRESS].len) {
				broadcast = broadcast_addr(subnet, netmask);
				if (broadcast.len)
					script_set_env(ip->client, prefix,
					    "broadcast_address",
					    piaddr(broadcast));
			}
		}
	}

	if (lease->filename)
		script_set_env(ip->client, prefix, "filename", lease->filename);
	if (lease->server_name)
		script_set_env(ip->client, prefix, "server_name",
		    lease->server_name);
	for (i = 0; i < 256; i++) {
		len = 0;

		if (ip->client->config->defaults[i].len) {
			if (lease->options[i].len) {
				switch (
				    ip->client->config->default_actions[i]) {
				case ACTION_DEFAULT:
					dp = lease->options[i].data;
					len = lease->options[i].len;
					break;
				case ACTION_SUPERSEDE:
supersede:
					dp = ip->client->
						config->defaults[i].data;
					len = ip->client->
						config->defaults[i].len;
					break;
				case ACTION_PREPEND:
					len = ip->client->
					    config->defaults[i].len +
					    lease->options[i].len;
					if (len >= sizeof(dbuf)) {
						warning("no space to %s %s",
						    "prepend option",
						    dhcp_options[i].name);
						goto supersede;
					}
					dp = dbuf;
					memcpy(dp,
						ip->client->
						config->defaults[i].data,
						ip->client->
						config->defaults[i].len);
					memcpy(dp + ip->client->
						config->defaults[i].len,
						lease->options[i].data,
						lease->options[i].len);
					dp[len] = '\0';
					break;
				case ACTION_APPEND:
					/*
					 * When we append, we assume that we're
					 * appending to text.  Some MS servers
					 * include a NUL byte at the end of
					 * the search string provided.
					 */
					len = ip->client->
					    config->defaults[i].len +
					    lease->options[i].len;
					if (len >= sizeof(dbuf)) {
						warning("no space to %s %s",
						    "append option",
						    dhcp_options[i].name);
						goto supersede;
					}
					memcpy(dbuf,
						lease->options[i].data,
						lease->options[i].len);
					for (dp = dbuf + lease->options[i].len;
					    dp > dbuf; dp--, len--)
						if (dp[-1] != '\0')
							break;
					memcpy(dp,
						ip->client->
						config->defaults[i].data,
						ip->client->
						config->defaults[i].len);
					dp = dbuf;
					dp[len] = '\0';
				}
			} else {
				dp = ip->client->
					config->defaults[i].data;
				len = ip->client->
					config->defaults[i].len;
			}
		} else if (lease->options[i].len) {
			len = lease->options[i].len;
			dp = lease->options[i].data;
		} else {
			len = 0;
		}
		if (len) {
			char name[256];

			if (dhcp_option_ev_name(name, sizeof(name),
			    &dhcp_options[i]))
				script_set_env(ip->client, prefix, name,
				    pretty_print_option(i, dp, len, 0, 0));
		}
	}
	snprintf(tbuf, sizeof(tbuf), "%d", (int)lease->expiry);
	script_set_env(ip->client, prefix, "expiry", tbuf);
}