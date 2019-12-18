#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_9__ {scalar_t__ gateway_ports; } ;
struct TYPE_8__ {char* listen_path; char* listen_host; int /*<<< orphan*/  connect_port; int /*<<< orphan*/ * connect_host; int /*<<< orphan*/ * connect_path; int /*<<< orphan*/  listen_port; } ;
struct TYPE_7__ {char* listen_path; char* listen_host; scalar_t__ handle; int /*<<< orphan*/  connect_port; int /*<<< orphan*/ * connect_host; int /*<<< orphan*/ * connect_path; int /*<<< orphan*/  listen_port; } ;
struct TYPE_6__ {int num_local_forwards; int num_remote_forwards; scalar_t__ tun_open; scalar_t__ exit_on_forward_failure; int /*<<< orphan*/  tun_remote; int /*<<< orphan*/  tun_local; TYPE_2__* remote_forwards; TYPE_4__ fwd_opts; TYPE_3__* local_forwards; } ;

/* Variables and functions */
 scalar_t__ SSH_TUNMODE_NO ; 
 scalar_t__ channel_request_remote_forwarding (struct ssh*,TYPE_2__*) ; 
 scalar_t__ channel_setup_local_fwd_listener (struct ssh*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  client_register_global_confirm (int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* client_request_tun_fwd (struct ssh*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  logit (char*) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  ssh_confirm_remote_forward ; 

__attribute__((used)) static void
ssh_init_forwarding(struct ssh *ssh, char **ifname)
{
	int success = 0;
	int i;

	/* Initiate local TCP/IP port forwardings. */
	for (i = 0; i < options.num_local_forwards; i++) {
		debug("Local connections to %.200s:%d forwarded to remote "
		    "address %.200s:%d",
		    (options.local_forwards[i].listen_path != NULL) ?
		    options.local_forwards[i].listen_path :
		    (options.local_forwards[i].listen_host == NULL) ?
		    (options.fwd_opts.gateway_ports ? "*" : "LOCALHOST") :
		    options.local_forwards[i].listen_host,
		    options.local_forwards[i].listen_port,
		    (options.local_forwards[i].connect_path != NULL) ?
		    options.local_forwards[i].connect_path :
		    options.local_forwards[i].connect_host,
		    options.local_forwards[i].connect_port);
		success += channel_setup_local_fwd_listener(ssh,
		    &options.local_forwards[i], &options.fwd_opts);
	}
	if (i > 0 && success != i && options.exit_on_forward_failure)
		fatal("Could not request local forwarding.");
	if (i > 0 && success == 0)
		error("Could not request local forwarding.");

	/* Initiate remote TCP/IP port forwardings. */
	for (i = 0; i < options.num_remote_forwards; i++) {
		debug("Remote connections from %.200s:%d forwarded to "
		    "local address %.200s:%d",
		    (options.remote_forwards[i].listen_path != NULL) ?
		    options.remote_forwards[i].listen_path :
		    (options.remote_forwards[i].listen_host == NULL) ?
		    "LOCALHOST" : options.remote_forwards[i].listen_host,
		    options.remote_forwards[i].listen_port,
		    (options.remote_forwards[i].connect_path != NULL) ?
		    options.remote_forwards[i].connect_path :
		    options.remote_forwards[i].connect_host,
		    options.remote_forwards[i].connect_port);
		options.remote_forwards[i].handle =
		    channel_request_remote_forwarding(ssh,
		    &options.remote_forwards[i]);
		if (options.remote_forwards[i].handle < 0) {
			if (options.exit_on_forward_failure)
				fatal("Could not request remote forwarding.");
			else
				logit("Warning: Could not request remote "
				    "forwarding.");
		} else {
			client_register_global_confirm(
			    ssh_confirm_remote_forward,
			    &options.remote_forwards[i]);
		}
	}

	/* Initiate tunnel forwarding. */
	if (options.tun_open != SSH_TUNMODE_NO) {
		if ((*ifname = client_request_tun_fwd(ssh,
		    options.tun_open, options.tun_local,
		    options.tun_remote)) == NULL) {
			if (options.exit_on_forward_failure)
				fatal("Could not request tunnel forwarding.");
			else
				error("Could not request tunnel forwarding.");
		}
	}
}