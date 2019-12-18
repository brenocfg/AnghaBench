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
struct ssh {int dummy; } ;
struct connection_info {int /*<<< orphan*/  rdomain; int /*<<< orphan*/  lport; int /*<<< orphan*/  laddress; int /*<<< orphan*/  address; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct ssh* active_state ; 
 int /*<<< orphan*/  auth_get_canonical_hostname (struct ssh*,int) ; 
 int /*<<< orphan*/  ssh_local_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_local_port (struct ssh*) ; 
 int /*<<< orphan*/  ssh_packet_rdomain_in (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 

struct connection_info *
get_connection_info(int populate, int use_dns)
{
	struct ssh *ssh = active_state; /* XXX */
	static struct connection_info ci;

	if (!populate)
		return &ci;
	ci.host = auth_get_canonical_hostname(ssh, use_dns);
	ci.address = ssh_remote_ipaddr(ssh);
	ci.laddress = ssh_local_ipaddr(ssh);
	ci.lport = ssh_local_port(ssh);
	ci.rdomain = ssh_packet_rdomain_in(ssh);
	return &ci;
}