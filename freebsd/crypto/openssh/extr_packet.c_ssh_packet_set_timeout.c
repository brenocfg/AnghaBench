#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ssh {struct session_state* state; } ;
struct session_state {int packet_timeout_ms; } ;

/* Variables and functions */
 int INT_MAX ; 

void
ssh_packet_set_timeout(struct ssh *ssh, int timeout, int count)
{
	struct session_state *state = ssh->state;

	if (timeout <= 0 || count <= 0) {
		state->packet_timeout_ms = -1;
		return;
	}
	if ((INT_MAX / 1000) / count < timeout)
		state->packet_timeout_ms = INT_MAX;
	else
		state->packet_timeout_ms = timeout * count * 1000;
}