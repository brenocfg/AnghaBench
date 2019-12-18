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
struct sshbuf {int dummy; } ;
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  outgoing_packet; } ;

/* Variables and functions */
 int sshbuf_putb (int /*<<< orphan*/ ,struct sshbuf const*) ; 

int
sshpkt_putb(struct ssh *ssh, const struct sshbuf *b)
{
	return sshbuf_putb(ssh->state->outgoing_packet, b);
}