#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ssh_channels {size_t channels_alloc; TYPE_1__** channels; } ;
struct ssh {struct ssh_channels* chanctxt; } ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 scalar_t__ SSH_CHANNEL_RDYNAMIC_OPEN ; 
 int /*<<< orphan*/  channel_before_prepare_select_rdynamic (struct ssh*,TYPE_1__*) ; 

__attribute__((used)) static void
channel_before_prepare_select(struct ssh *ssh)
{
	struct ssh_channels *sc = ssh->chanctxt;
	Channel *c;
	u_int i, oalloc;

	for (i = 0, oalloc = sc->channels_alloc; i < oalloc; i++) {
		c = sc->channels[i];
		if (c == NULL)
			continue;
		if (c->type == SSH_CHANNEL_RDYNAMIC_OPEN)
			channel_before_prepare_select_rdynamic(ssh, c);
	}
}