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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {int dummy; } ;
struct Forward {char* listen_path; char* listen_host; char* listen_port; int allocated_port; int /*<<< orphan*/  handle; int /*<<< orphan*/  connect_port; scalar_t__ connect_host; scalar_t__ connect_path; } ;
struct TYPE_2__ {scalar_t__ num_remote_forwards; scalar_t__ exit_on_forward_failure; } ;

/* Variables and functions */
 int SSH2_MSG_REQUEST_FAILURE ; 
 int SSH2_MSG_REQUEST_SUCCESS ; 
 int /*<<< orphan*/  channel_update_permission (struct ssh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 scalar_t__ fork_after_authentication_flag ; 
 int /*<<< orphan*/  fork_postauth () ; 
 int /*<<< orphan*/  logit (char*,...) ; 
 TYPE_1__ options ; 
 int packet_get_int () ; 
 scalar_t__ remote_forward_confirms_received ; 

__attribute__((used)) static void
ssh_confirm_remote_forward(struct ssh *ssh, int type, u_int32_t seq, void *ctxt)
{
	struct Forward *rfwd = (struct Forward *)ctxt;

	/* XXX verbose() on failure? */
	debug("remote forward %s for: listen %s%s%d, connect %s:%d",
	    type == SSH2_MSG_REQUEST_SUCCESS ? "success" : "failure",
	    rfwd->listen_path ? rfwd->listen_path :
	    rfwd->listen_host ? rfwd->listen_host : "",
	    (rfwd->listen_path || rfwd->listen_host) ? ":" : "",
	    rfwd->listen_port, rfwd->connect_path ? rfwd->connect_path :
	    rfwd->connect_host, rfwd->connect_port);
	if (rfwd->listen_path == NULL && rfwd->listen_port == 0) {
		if (type == SSH2_MSG_REQUEST_SUCCESS) {
			rfwd->allocated_port = packet_get_int();
			logit("Allocated port %u for remote forward to %s:%d",
			    rfwd->allocated_port,
			    rfwd->connect_host, rfwd->connect_port);
			channel_update_permission(ssh,
			    rfwd->handle, rfwd->allocated_port);
		} else {
			channel_update_permission(ssh, rfwd->handle, -1);
		}
	}

	if (type == SSH2_MSG_REQUEST_FAILURE) {
		if (options.exit_on_forward_failure) {
			if (rfwd->listen_path != NULL)
				fatal("Error: remote port forwarding failed "
				    "for listen path %s", rfwd->listen_path);
			else
				fatal("Error: remote port forwarding failed "
				    "for listen port %d", rfwd->listen_port);
		} else {
			if (rfwd->listen_path != NULL)
				logit("Warning: remote port forwarding failed "
				    "for listen path %s", rfwd->listen_path);
			else
				logit("Warning: remote port forwarding failed "
				    "for listen port %d", rfwd->listen_port);
		}
	}
	if (++remote_forward_confirms_received == options.num_remote_forwards) {
		debug("All remote forwarding requests processed");
		if (fork_after_authentication_flag)
			fork_postauth();
	}
}