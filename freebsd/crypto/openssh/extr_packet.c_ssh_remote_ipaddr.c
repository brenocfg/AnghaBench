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
struct ssh {char const* remote_ipaddr; int remote_port; int local_port; void* local_ipaddr; TYPE_1__* state; } ;
struct TYPE_2__ {int connection_in; } ;

/* Variables and functions */
 void* get_local_ipaddr (int) ; 
 int get_local_port (int) ; 
 char const* get_peer_ipaddr (int) ; 
 int get_peer_port (int) ; 
 scalar_t__ ssh_packet_connection_is_on_socket (struct ssh*) ; 
 void* strdup (char*) ; 

const char *
ssh_remote_ipaddr(struct ssh *ssh)
{
	int sock;

	/* Check whether we have cached the ipaddr. */
	if (ssh->remote_ipaddr == NULL) {
		if (ssh_packet_connection_is_on_socket(ssh)) {
			sock = ssh->state->connection_in;
			ssh->remote_ipaddr = get_peer_ipaddr(sock);
			ssh->remote_port = get_peer_port(sock);
			ssh->local_ipaddr = get_local_ipaddr(sock);
			ssh->local_port = get_local_port(sock);
		} else {
			ssh->remote_ipaddr = strdup("UNKNOWN");
			ssh->remote_port = 65535;
			ssh->local_ipaddr = strdup("UNKNOWN");
			ssh->local_port = 65535;
		}
	}
	return ssh->remote_ipaddr;
}