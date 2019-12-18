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
typedef  scalar_t__ u_int32_t ;
struct ssh {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  error (char*,char const*,scalar_t__,...) ; 
 char* ssh_err (int) ; 
 int /*<<< orphan*/  ssh_packet_disconnect (struct ssh*,char*,char const*) ; 
 int sshpkt_get_u32 (struct ssh*,scalar_t__*) ; 

__attribute__((used)) static int
channel_parse_id(struct ssh *ssh, const char *where, const char *what)
{
	u_int32_t id;
	int r;

	if ((r = sshpkt_get_u32(ssh, &id)) != 0) {
		error("%s: parse id: %s", where, ssh_err(r));
		ssh_packet_disconnect(ssh, "Invalid %s message", what);
	}
	if (id > INT_MAX) {
		error("%s: bad channel id %u: %s", where, id, ssh_err(r));
		ssh_packet_disconnect(ssh, "Invalid %s channel id", what);
	}
	return (int)id;
}