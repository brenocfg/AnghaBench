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
struct TYPE_4__ {scalar_t__ packets; } ;
struct TYPE_3__ {scalar_t__ packets; } ;
struct ssh {int connection_in; int connection_out; int max_packet_size; int packet_timeout_ms; int initialized; int rekeying; int /*<<< orphan*/ * outgoing_packet; int /*<<< orphan*/ * incoming_packet; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; struct ssh* state; TYPE_2__ p_read; TYPE_1__ p_send; int /*<<< orphan*/  public_keys; int /*<<< orphan*/  private_keys; int /*<<< orphan*/  outgoing; } ;
struct session_state {int connection_in; int connection_out; int max_packet_size; int packet_timeout_ms; int initialized; int rekeying; int /*<<< orphan*/ * outgoing_packet; int /*<<< orphan*/ * incoming_packet; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; struct session_state* state; TYPE_2__ p_read; TYPE_1__ p_send; int /*<<< orphan*/  public_keys; int /*<<< orphan*/  private_keys; int /*<<< orphan*/  outgoing; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct ssh* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ssh*) ; 
 int /*<<< orphan*/  sshbuf_free (int /*<<< orphan*/ *) ; 
 void* sshbuf_new () ; 

struct ssh *
ssh_alloc_session_state(void)
{
	struct ssh *ssh = NULL;
	struct session_state *state = NULL;

	if ((ssh = calloc(1, sizeof(*ssh))) == NULL ||
	    (state = calloc(1, sizeof(*state))) == NULL ||
	    (state->input = sshbuf_new()) == NULL ||
	    (state->output = sshbuf_new()) == NULL ||
	    (state->outgoing_packet = sshbuf_new()) == NULL ||
	    (state->incoming_packet = sshbuf_new()) == NULL)
		goto fail;
	TAILQ_INIT(&state->outgoing);
	TAILQ_INIT(&ssh->private_keys);
	TAILQ_INIT(&ssh->public_keys);
	state->connection_in = -1;
	state->connection_out = -1;
	state->max_packet_size = 32768;
	state->packet_timeout_ms = -1;
	state->p_send.packets = state->p_read.packets = 0;
	state->initialized = 1;
	/*
	 * ssh_packet_send2() needs to queue packets until
	 * we've done the initial key exchange.
	 */
	state->rekeying = 1;
	ssh->state = state;
	return ssh;
 fail:
	if (state) {
		sshbuf_free(state->input);
		sshbuf_free(state->output);
		sshbuf_free(state->incoming_packet);
		sshbuf_free(state->outgoing_packet);
		free(state);
	}
	free(ssh);
	return NULL;
}