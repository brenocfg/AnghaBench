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
typedef  int /*<<< orphan*/  u ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct protocol {int /*<<< orphan*/  fd; struct interface_info* local; } ;
struct interface_info {int errors; int dead; int /*<<< orphan*/  name; scalar_t__ noifmedia; } ;
struct iaddr {int len; int /*<<< orphan*/  iabuf; } ;
struct hardware {int dummy; } ;
struct dhcp_packet {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  bootp_packet_handler (struct interface_info*,struct dhcp_packet*,int,int /*<<< orphan*/ ,struct iaddr,struct hardware*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct interface_info*) ; 
 int /*<<< orphan*/  interface_status (struct interface_info*) ; 
 int interfaces_invalidated ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int receive_packet (struct interface_info*,unsigned char*,int,struct sockaddr_in*,struct hardware*) ; 
 int /*<<< orphan*/  remove_protocol (struct protocol*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct interface_info*,struct dhcp_packet*,int,int /*<<< orphan*/ ,struct iaddr,struct hardware*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,...) ; 

void
got_one(struct protocol *l)
{
	struct sockaddr_in from;
	struct hardware hfrom;
	struct iaddr ifrom;
	ssize_t result;
	union {
		/*
		 * Packet input buffer.  Must be as large as largest
		 * possible MTU.
		 */
		unsigned char packbuf[4095];
		struct dhcp_packet packet;
	} u;
	struct interface_info *ip = l->local;

	if ((result = receive_packet(ip, u.packbuf, sizeof(u), &from,
	    &hfrom)) == -1) {
		warning("receive_packet failed on %s: %s", ip->name,
		    strerror(errno));
		ip->errors++;
		if ((!interface_status(ip)) ||
		    (ip->noifmedia && ip->errors > 20)) {
			/* our interface has gone away. */
			warning("Interface %s no longer appears valid.",
			    ip->name);
			ip->dead = 1;
			interfaces_invalidated = 1;
			close(l->fd);
			remove_protocol(l);
			free(ip);
		}
		return;
	}
	if (result == 0)
		return;

	if (bootp_packet_handler) {
		ifrom.len = 4;
		memcpy(ifrom.iabuf, &from.sin_addr, ifrom.len);

		(*bootp_packet_handler)(ip, &u.packet, result,
		    from.sin_port, ifrom, &hfrom);
	}
}