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
struct TYPE_2__ {int /*<<< orphan*/  output; scalar_t__ interactive_mode; } ;

/* Variables and functions */
 int sshbuf_len (int /*<<< orphan*/ ) ; 

int
ssh_packet_not_very_much_data_to_write(struct ssh *ssh)
{
	if (ssh->state->interactive_mode)
		return sshbuf_len(ssh->state->output) < 16384;
	else
		return sshbuf_len(ssh->state->output) < 128 * 1024;
}