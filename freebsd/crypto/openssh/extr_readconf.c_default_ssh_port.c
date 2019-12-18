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
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int SSH_DEFAULT_PORT ; 
 int /*<<< orphan*/  SSH_SERVICE_NAME ; 
 struct servent* getservbyname (int /*<<< orphan*/ ,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

int
default_ssh_port(void)
{
	static int port;
	struct servent *sp;

	if (port == 0) {
		sp = getservbyname(SSH_SERVICE_NAME, "tcp");
		port = sp ? ntohs(sp->s_port) : SSH_DEFAULT_PORT;
	}
	return port;
}