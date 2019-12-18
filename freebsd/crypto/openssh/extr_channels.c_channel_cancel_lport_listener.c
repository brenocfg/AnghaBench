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
struct Forward {int /*<<< orphan*/  listen_port; int /*<<< orphan*/  listen_host; int /*<<< orphan*/ * listen_path; } ;

/* Variables and functions */
 int channel_cancel_lport_listener_streamlocal (struct ssh*,int /*<<< orphan*/ *) ; 
 int channel_cancel_lport_listener_tcpip (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ForwardOptions*) ; 

int
channel_cancel_lport_listener(struct ssh *ssh,
    struct Forward *fwd, int cport, struct ForwardOptions *fwd_opts)
{
	if (fwd->listen_path != NULL) {
		return channel_cancel_lport_listener_streamlocal(ssh,
		    fwd->listen_path);
	} else {
		return channel_cancel_lport_listener_tcpip(ssh,
		    fwd->listen_host, fwd->listen_port, cport, fwd_opts);
	}
}