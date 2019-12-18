#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
#define  SSH_CHANNEL_ABANDONED 137 
#define  SSH_CHANNEL_CONNECTING 136 
#define  SSH_CHANNEL_DYNAMIC 135 
#define  SSH_CHANNEL_LARVAL 134 
#define  SSH_CHANNEL_MUX_PROXY 133 
#define  SSH_CHANNEL_OPEN 132 
#define  SSH_CHANNEL_OPENING 131 
#define  SSH_CHANNEL_RDYNAMIC_FINISH 130 
#define  SSH_CHANNEL_RDYNAMIC_OPEN 129 
#define  SSH_CHANNEL_X11_OPEN 128 
 TYPE_1__* channel_by_id (struct ssh*,int) ; 
 int /*<<< orphan*/  logit (char*,int,int) ; 

Channel *
channel_lookup(struct ssh *ssh, int id)
{
	Channel *c;

	if ((c = channel_by_id(ssh, id)) == NULL)
		return NULL;

	switch (c->type) {
	case SSH_CHANNEL_X11_OPEN:
	case SSH_CHANNEL_LARVAL:
	case SSH_CHANNEL_CONNECTING:
	case SSH_CHANNEL_DYNAMIC:
	case SSH_CHANNEL_RDYNAMIC_OPEN:
	case SSH_CHANNEL_RDYNAMIC_FINISH:
	case SSH_CHANNEL_OPENING:
	case SSH_CHANNEL_OPEN:
	case SSH_CHANNEL_ABANDONED:
	case SSH_CHANNEL_MUX_PROXY:
		return c;
	}
	logit("Non-public channel %d, type %d.", id, c->type);
	return NULL;
}