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
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  outgoing_packet; } ;

/* Variables and functions */
 int sshbuf_put_string (int /*<<< orphan*/ ,void const*,size_t) ; 

int
sshpkt_put_string(struct ssh *ssh, const void *v, size_t len)
{
	return sshbuf_put_string(ssh->state->outgoing_packet, v, len);
}