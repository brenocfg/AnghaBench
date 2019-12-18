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
struct interface_info {TYPE_1__* client; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  packet_length; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  REMOTE_PORT ; 
 int /*<<< orphan*/  inaddr_any ; 
 int /*<<< orphan*/  inaddr_broadcast ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  privfd ; 
 int /*<<< orphan*/  send_packet_unpriv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
send_decline(void *ipp)
{
	struct interface_info *ip = ipp;

	note("DHCPDECLINE on %s to %s port %d", ip->name,
	    inet_ntoa(inaddr_broadcast), REMOTE_PORT);

	/* Send out a packet. */
	send_packet_unpriv(privfd, &ip->client->packet,
	    ip->client->packet_length, inaddr_any, inaddr_broadcast);
}