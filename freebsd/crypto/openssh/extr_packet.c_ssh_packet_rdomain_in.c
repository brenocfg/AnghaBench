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
struct ssh {char const* rdomain_in; TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  connection_in; } ;

/* Variables and functions */
 char const* get_rdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_packet_connection_is_on_socket (struct ssh*) ; 

const char *
ssh_packet_rdomain_in(struct ssh *ssh)
{
	if (ssh->rdomain_in != NULL)
		return ssh->rdomain_in;
	if (!ssh_packet_connection_is_on_socket(ssh))
		return NULL;
	ssh->rdomain_in = get_rdomain(ssh->state->connection_in);
	return ssh->rdomain_in;
}