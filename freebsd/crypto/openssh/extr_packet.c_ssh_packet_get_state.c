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
struct sshbuf {int dummy; } ;
struct ssh {int /*<<< orphan*/  kex; struct session_state* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  blocks; int /*<<< orphan*/  seqnr; } ;
struct TYPE_3__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  blocks; int /*<<< orphan*/  seqnr; } ;
struct session_state {int /*<<< orphan*/  output; int /*<<< orphan*/  input; TYPE_2__ p_read; TYPE_1__ p_send; int /*<<< orphan*/  rekey_interval; int /*<<< orphan*/  rekey_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_IN ; 
 int /*<<< orphan*/  MODE_OUT ; 
 int kex_to_blob (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int newkeys_to_blob (struct sshbuf*,struct ssh*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_stringb (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u32 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u64 (struct sshbuf*,int /*<<< orphan*/ ) ; 

int
ssh_packet_get_state(struct ssh *ssh, struct sshbuf *m)
{
	struct session_state *state = ssh->state;
	int r;

	if ((r = kex_to_blob(m, ssh->kex)) != 0 ||
	    (r = newkeys_to_blob(m, ssh, MODE_OUT)) != 0 ||
	    (r = newkeys_to_blob(m, ssh, MODE_IN)) != 0 ||
	    (r = sshbuf_put_u64(m, state->rekey_limit)) != 0 ||
	    (r = sshbuf_put_u32(m, state->rekey_interval)) != 0 ||
	    (r = sshbuf_put_u32(m, state->p_send.seqnr)) != 0 ||
	    (r = sshbuf_put_u64(m, state->p_send.blocks)) != 0 ||
	    (r = sshbuf_put_u32(m, state->p_send.packets)) != 0 ||
	    (r = sshbuf_put_u64(m, state->p_send.bytes)) != 0 ||
	    (r = sshbuf_put_u32(m, state->p_read.seqnr)) != 0 ||
	    (r = sshbuf_put_u64(m, state->p_read.blocks)) != 0 ||
	    (r = sshbuf_put_u32(m, state->p_read.packets)) != 0 ||
	    (r = sshbuf_put_u64(m, state->p_read.bytes)) != 0 ||
	    (r = sshbuf_put_stringb(m, state->input)) != 0 ||
	    (r = sshbuf_put_stringb(m, state->output)) != 0)
		return r;

	return 0;
}