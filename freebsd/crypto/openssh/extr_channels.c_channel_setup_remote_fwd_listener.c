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
struct ForwardOptions {int dummy; } ;
struct Forward {int /*<<< orphan*/ * listen_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_CHANNEL_RPORT_LISTENER ; 
 int /*<<< orphan*/  SSH_CHANNEL_RUNIX_LISTENER ; 
 int channel_setup_fwd_listener_streamlocal (struct ssh*,int /*<<< orphan*/ ,struct Forward*,struct ForwardOptions*) ; 
 int channel_setup_fwd_listener_tcpip (struct ssh*,int /*<<< orphan*/ ,struct Forward*,int*,struct ForwardOptions*) ; 
 int /*<<< orphan*/  check_rfwd_permission (struct ssh*,struct Forward*) ; 
 int /*<<< orphan*/  packet_send_debug (char*) ; 

int
channel_setup_remote_fwd_listener(struct ssh *ssh, struct Forward *fwd,
    int *allocated_listen_port, struct ForwardOptions *fwd_opts)
{
	if (!check_rfwd_permission(ssh, fwd)) {
		packet_send_debug("port forwarding refused");
		return 0;
	}
	if (fwd->listen_path != NULL) {
		return channel_setup_fwd_listener_streamlocal(ssh,
		    SSH_CHANNEL_RUNIX_LISTENER, fwd, fwd_opts);
	} else {
		return channel_setup_fwd_listener_tcpip(ssh,
		    SSH_CHANNEL_RPORT_LISTENER, fwd, allocated_listen_port,
		    fwd_opts);
	}
}