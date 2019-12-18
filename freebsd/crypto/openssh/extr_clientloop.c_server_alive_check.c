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
struct TYPE_2__ {scalar_t__ server_alive_count_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_GLOBAL_REQUEST ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 int /*<<< orphan*/  client_register_global_confirm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ options ; 
 scalar_t__ packet_inc_alive_timeouts () ; 
 int /*<<< orphan*/  packet_put_char (int) ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
server_alive_check(void)
{
	if (packet_inc_alive_timeouts() > options.server_alive_count_max) {
		logit("Timeout, server %s not responding.", host);
		cleanup_exit(255);
	}
	packet_start(SSH2_MSG_GLOBAL_REQUEST);
	packet_put_cstring("keepalive@openssh.com");
	packet_put_char(1);     /* boolean: want reply */
	packet_send();
	/* Insert an empty placeholder to maintain ordering */
	client_register_global_confirm(NULL, NULL);
}