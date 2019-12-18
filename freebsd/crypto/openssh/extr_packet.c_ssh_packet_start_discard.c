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
typedef  scalar_t__ u_int ;
struct sshmac {scalar_t__ enabled; scalar_t__ etm; } ;
struct sshenc {int /*<<< orphan*/  cipher; } ;
struct ssh {struct session_state* state; } ;
struct session_state {size_t packet_discard_mac_already; int /*<<< orphan*/  input; scalar_t__ packet_discard; struct sshmac* packet_discard_mac; } ;

/* Variables and functions */
 int SSH_ERR_MAC_INVALID ; 
 int /*<<< orphan*/  cipher_is_cbc (int /*<<< orphan*/ ) ; 
 int ssh_packet_stop_discard (struct ssh*) ; 
 scalar_t__ sshbuf_len (int /*<<< orphan*/ ) ; 
 int sshpkt_disconnect (struct ssh*,char*) ; 

__attribute__((used)) static int
ssh_packet_start_discard(struct ssh *ssh, struct sshenc *enc,
    struct sshmac *mac, size_t mac_already, u_int discard)
{
	struct session_state *state = ssh->state;
	int r;

	if (enc == NULL || !cipher_is_cbc(enc->cipher) || (mac && mac->etm)) {
		if ((r = sshpkt_disconnect(ssh, "Packet corrupt")) != 0)
			return r;
		return SSH_ERR_MAC_INVALID;
	}
	/*
	 * Record number of bytes over which the mac has already
	 * been computed in order to minimize timing attacks.
	 */
	if (mac && mac->enabled) {
		state->packet_discard_mac = mac;
		state->packet_discard_mac_already = mac_already;
	}
	if (sshbuf_len(state->input) >= discard)
		return ssh_packet_stop_discard(ssh);
	state->packet_discard = discard - sshbuf_len(state->input);
	return 0;
}