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
typedef  int /*<<< orphan*/  u_char ;
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  incoming_packet; } ;

/* Variables and functions */
 size_t sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* sshbuf_ptr (int /*<<< orphan*/ ) ; 

const u_char *
sshpkt_ptr(struct ssh *ssh, size_t *lenp)
{
	if (lenp != NULL)
		*lenp = sshbuf_len(ssh->state->incoming_packet);
	return sshbuf_ptr(ssh->state->incoming_packet);
}