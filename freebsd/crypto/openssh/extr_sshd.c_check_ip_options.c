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
typedef  int u_char ;
typedef  int /*<<< orphan*/  text ;
struct ssh {int dummy; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  from ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_OPTIONS ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,scalar_t__*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int ssh_packet_get_connection_in (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 

__attribute__((used)) static void
check_ip_options(struct ssh *ssh)
{
#ifdef IP_OPTIONS
	int sock_in = ssh_packet_get_connection_in(ssh);
	struct sockaddr_storage from;
	u_char opts[200];
	socklen_t i, option_size = sizeof(opts), fromlen = sizeof(from);
	char text[sizeof(opts) * 3 + 1];

	memset(&from, 0, sizeof(from));
	if (getpeername(sock_in, (struct sockaddr *)&from,
	    &fromlen) < 0)
		return;
	if (from.ss_family != AF_INET)
		return;
	/* XXX IPv6 options? */

	if (getsockopt(sock_in, IPPROTO_IP, IP_OPTIONS, opts,
	    &option_size) >= 0 && option_size != 0) {
		text[0] = '\0';
		for (i = 0; i < option_size; i++)
			snprintf(text + i*3, sizeof(text) - i*3,
			    " %2.2x", opts[i]);
		fatal("Connection from %.100s port %d with IP opts: %.800s",
		    ssh_remote_ipaddr(ssh), ssh_remote_port(ssh), text);
	}
	return;
#endif /* IP_OPTIONS */
}