#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ssh {TYPE_1__* chanctxt; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  sock; } ;
struct TYPE_4__ {size_t channels_alloc; TYPE_2__** channels; } ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */
#define  SSH_CHANNEL_AUTH_SOCKET 133 
#define  SSH_CHANNEL_PORT_LISTENER 132 
#define  SSH_CHANNEL_RPORT_LISTENER 131 
#define  SSH_CHANNEL_RUNIX_LISTENER 130 
#define  SSH_CHANNEL_UNIX_LISTENER 129 
#define  SSH_CHANNEL_X11_LISTENER 128 
 int /*<<< orphan*/  channel_close_fd (struct ssh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_free (struct ssh*,TYPE_2__*) ; 

void
channel_stop_listening(struct ssh *ssh)
{
	u_int i;
	Channel *c;

	for (i = 0; i < ssh->chanctxt->channels_alloc; i++) {
		c = ssh->chanctxt->channels[i];
		if (c != NULL) {
			switch (c->type) {
			case SSH_CHANNEL_AUTH_SOCKET:
			case SSH_CHANNEL_PORT_LISTENER:
			case SSH_CHANNEL_RPORT_LISTENER:
			case SSH_CHANNEL_X11_LISTENER:
			case SSH_CHANNEL_UNIX_LISTENER:
			case SSH_CHANNEL_RUNIX_LISTENER:
				channel_close_fd(ssh, &c->sock);
				channel_free(ssh, c);
				break;
			}
		}
	}
}