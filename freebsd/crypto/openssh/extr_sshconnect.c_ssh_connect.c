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
typedef  int /*<<< orphan*/  u_short ;
struct ssh {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct addrinfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * proxy_command; scalar_t__ proxy_use_fdpass; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 TYPE_1__ options ; 
 int ssh_connect_direct (struct ssh*,char const*,struct addrinfo*,struct sockaddr_storage*,int /*<<< orphan*/ ,int,int,int*,int) ; 
 int /*<<< orphan*/ * ssh_packet_set_connection (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssh_proxy_connect (struct ssh*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ssh_proxy_fdpass_connect (struct ssh*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

int
ssh_connect(struct ssh *ssh, const char *host, struct addrinfo *addrs,
    struct sockaddr_storage *hostaddr, u_short port, int family,
    int connection_attempts, int *timeout_ms, int want_keepalive)
{
	if (options.proxy_command == NULL) {
		return ssh_connect_direct(ssh, host, addrs, hostaddr, port,
		    family, connection_attempts, timeout_ms, want_keepalive);
	} else if (strcmp(options.proxy_command, "-") == 0) {
		if ((ssh_packet_set_connection(ssh,
		    STDIN_FILENO, STDOUT_FILENO)) == NULL)
			return -1; /* ssh_packet_set_connection logs error */
		return 0;
	} else if (options.proxy_use_fdpass) {
		return ssh_proxy_fdpass_connect(ssh, host, port,
		    options.proxy_command);
	}
	return ssh_proxy_connect(ssh, host, port, options.proxy_command);
}