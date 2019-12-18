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
typedef  size_t u_int ;
struct ssh {TYPE_1__* chanctxt; } ;
struct TYPE_2__ {size_t channels_alloc; int /*<<< orphan*/ ** channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_close_fds (struct ssh*,int /*<<< orphan*/ *) ; 

void
channel_close_all(struct ssh *ssh)
{
	u_int i;

	for (i = 0; i < ssh->chanctxt->channels_alloc; i++)
		if (ssh->chanctxt->channels[i] != NULL)
			channel_close_fds(ssh, ssh->chanctxt->channels[i]);
}