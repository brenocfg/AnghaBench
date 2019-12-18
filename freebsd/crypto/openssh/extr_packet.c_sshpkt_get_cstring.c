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
struct TYPE_2__ {int /*<<< orphan*/  incoming_packet; } ;

/* Variables and functions */
 int sshbuf_get_cstring (int /*<<< orphan*/ ,char**,size_t*) ; 

int
sshpkt_get_cstring(struct ssh *ssh, char **valp, size_t *lenp)
{
	return sshbuf_get_cstring(ssh->state->incoming_packet, valp, lenp);
}