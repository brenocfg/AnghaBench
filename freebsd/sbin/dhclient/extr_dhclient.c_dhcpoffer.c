#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct packet {TYPE_3__* options; TYPE_2__* raw; int /*<<< orphan*/  client_addr; struct interface_info* interface; } ;
struct TYPE_8__ {scalar_t__ hlen; int /*<<< orphan*/  haddr; } ;
struct interface_info {TYPE_7__* client; TYPE_1__ hw_address; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/  iabuf; } ;
struct client_lease {int is_bootp; struct client_lease* next; TYPE_5__ address; int /*<<< orphan*/  medium; } ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/ * iabuf; } ;
struct TYPE_14__ {scalar_t__ state; scalar_t__ xid; int first_sending; struct client_lease* offered_leases; TYPE_6__ requested_address; TYPE_4__* config; int /*<<< orphan*/  medium; } ;
struct TYPE_11__ {int* required_options; int select_interval; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_9__ {scalar_t__ xid; scalar_t__ hlen; int /*<<< orphan*/  yiaddr; int /*<<< orphan*/ * chaddr; } ;

/* Variables and functions */
 size_t DHO_DHCP_MESSAGE_TYPE ; 
 scalar_t__ S_SELECTING ; 
 int /*<<< orphan*/  add_timeout (int,int /*<<< orphan*/  (*) (struct interface_info*),struct interface_info*) ; 
 int /*<<< orphan*/  cancel_timeout (int /*<<< orphan*/ ,struct interface_info*) ; 
 int cur_time ; 
 int /*<<< orphan*/  debug (char*,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  note (char*,...) ; 
 struct client_lease* packet_to_lease (struct packet*) ; 
 int /*<<< orphan*/  piaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ script_go () ; 
 int /*<<< orphan*/  script_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_write_params (char*,struct client_lease*) ; 
 int /*<<< orphan*/  send_discover ; 
 int /*<<< orphan*/  state_selecting (struct interface_info*) ; 

void
dhcpoffer(struct packet *packet)
{
	struct interface_info *ip = packet->interface;
	struct client_lease *lease, *lp;
	int i;
	int arp_timeout_needed, stop_selecting;
	const char *name = packet->options[DHO_DHCP_MESSAGE_TYPE].len ?
	    "DHCPOFFER" : "BOOTREPLY";

	/* If we're not receptive to an offer right now, or if the offer
	   has an unrecognizable transaction id, then just drop it. */
	if (ip->client->state != S_SELECTING ||
	    packet->interface->client->xid != packet->raw->xid ||
	    (packet->interface->hw_address.hlen != packet->raw->hlen) ||
	    (memcmp(packet->interface->hw_address.haddr,
	    packet->raw->chaddr, packet->raw->hlen)))
		return;

	note("%s from %s", name, piaddr(packet->client_addr));


	/* If this lease doesn't supply the minimum required parameters,
	   blow it off. */
	for (i = 0; ip->client->config->required_options[i]; i++) {
		if (!packet->options[ip->client->config->
		    required_options[i]].len) {
			note("%s isn't satisfactory.", name);
			return;
		}
	}

	/* If we've already seen this lease, don't record it again. */
	for (lease = ip->client->offered_leases;
	    lease; lease = lease->next) {
		if (lease->address.len == sizeof(packet->raw->yiaddr) &&
		    !memcmp(lease->address.iabuf,
		    &packet->raw->yiaddr, lease->address.len)) {
			debug("%s already seen.", name);
			return;
		}
	}

	lease = packet_to_lease(packet);
	if (!lease) {
		note("packet_to_lease failed.");
		return;
	}

	/* If this lease was acquired through a BOOTREPLY, record that
	   fact. */
	if (!packet->options[DHO_DHCP_MESSAGE_TYPE].len)
		lease->is_bootp = 1;

	/* Record the medium under which this lease was offered. */
	lease->medium = ip->client->medium;

	/* Send out an ARP Request for the offered IP address. */
	script_init("ARPSEND", lease->medium);
	script_write_params("check_", lease);
	/* If the script can't send an ARP request without waiting,
	   we'll be waiting when we do the ARPCHECK, so don't wait now. */
	if (script_go())
		arp_timeout_needed = 0;
	else
		arp_timeout_needed = 2;

	/* Figure out when we're supposed to stop selecting. */
	stop_selecting =
	    ip->client->first_sending + ip->client->config->select_interval;

	/* If this is the lease we asked for, put it at the head of the
	   list, and don't mess with the arp request timeout. */
	if (lease->address.len == ip->client->requested_address.len &&
	    !memcmp(lease->address.iabuf,
	    ip->client->requested_address.iabuf,
	    ip->client->requested_address.len)) {
		lease->next = ip->client->offered_leases;
		ip->client->offered_leases = lease;
	} else {
		/* If we already have an offer, and arping for this
		   offer would take us past the selection timeout,
		   then don't extend the timeout - just hope for the
		   best. */
		if (ip->client->offered_leases &&
		    (cur_time + arp_timeout_needed) > stop_selecting)
			arp_timeout_needed = 0;

		/* Put the lease at the end of the list. */
		lease->next = NULL;
		if (!ip->client->offered_leases)
			ip->client->offered_leases = lease;
		else {
			for (lp = ip->client->offered_leases; lp->next;
			    lp = lp->next)
				;	/* nothing */
			lp->next = lease;
		}
	}

	/* If we're supposed to stop selecting before we've had time
	   to wait for the ARPREPLY, add some delay to wait for
	   the ARPREPLY. */
	if (stop_selecting - cur_time < arp_timeout_needed)
		stop_selecting = cur_time + arp_timeout_needed;

	/* If the selecting interval has expired, go immediately to
	   state_selecting().  Otherwise, time out into
	   state_selecting at the select interval. */
	if (stop_selecting <= 0)
		state_selecting(ip);
	else {
		add_timeout(stop_selecting, state_selecting, ip);
		cancel_timeout(send_discover, ip);
	}
}