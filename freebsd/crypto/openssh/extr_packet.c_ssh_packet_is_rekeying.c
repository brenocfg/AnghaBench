#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {TYPE_2__* kex; TYPE_1__* state; } ;
struct TYPE_4__ {scalar_t__ done; } ;
struct TYPE_3__ {scalar_t__ rekeying; } ;

/* Variables and functions */

int
ssh_packet_is_rekeying(struct ssh *ssh)
{
	return ssh->state->rekeying ||
	    (ssh->kex != NULL && ssh->kex->done == 0);
}