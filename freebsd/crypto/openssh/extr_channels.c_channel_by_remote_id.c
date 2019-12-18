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
struct TYPE_5__ {size_t remote_id; scalar_t__ have_remote_id; } ;
struct TYPE_4__ {size_t channels_alloc; TYPE_2__** channels; } ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */

Channel *
channel_by_remote_id(struct ssh *ssh, u_int remote_id)
{
	Channel *c;
	u_int i;

	for (i = 0; i < ssh->chanctxt->channels_alloc; i++) {
		c = ssh->chanctxt->channels[i];
		if (c != NULL && c->have_remote_id && c->remote_id == remote_id)
			return c;
	}
	return NULL;
}