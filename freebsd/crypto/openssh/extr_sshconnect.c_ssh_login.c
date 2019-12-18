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
struct sockaddr {int dummy; } ;
struct passwd {char const* pw_name; } ;
struct TYPE_2__ {char* user; } ;
typedef  int /*<<< orphan*/  Sensitive ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lowercase (char*) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  packet_set_nonblocking () ; 
 int /*<<< orphan*/  ssh_exchange_identification (int) ; 
 int /*<<< orphan*/  ssh_kex2 (char*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_userauth2 (char*,char*,char*,int /*<<< orphan*/ *) ; 
 char* xstrdup (char const*) ; 

void
ssh_login(Sensitive *sensitive, const char *orighost,
    struct sockaddr *hostaddr, u_short port, struct passwd *pw, int timeout_ms)
{
	char *host;
	char *server_user, *local_user;

	local_user = xstrdup(pw->pw_name);
	server_user = options.user ? options.user : local_user;

	/* Convert the user-supplied hostname into all lowercase. */
	host = xstrdup(orighost);
	lowercase(host);

	/* Exchange protocol version identification strings with the server. */
	ssh_exchange_identification(timeout_ms);

	/* Put the connection into non-blocking mode. */
	packet_set_nonblocking();

	/* key exchange */
	/* authenticate user */
	debug("Authenticating to %s:%d as '%s'", host, port, server_user);
	ssh_kex2(host, hostaddr, port);
	ssh_userauth2(local_user, server_user, host, sensitive);
	free(local_user);
}