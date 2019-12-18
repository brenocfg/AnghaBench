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
struct ssh {int remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 

int
ssh_remote_port(struct ssh *ssh)
{
	(void)ssh_remote_ipaddr(ssh); /* Will lookup and cache. */
	return ssh->remote_port;
}