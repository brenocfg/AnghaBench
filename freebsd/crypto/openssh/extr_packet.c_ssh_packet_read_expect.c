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
typedef  scalar_t__ u_char ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int SSH_ERR_PROTOCOL_ERROR ; 
 int ssh_packet_read_seqnr (struct ssh*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int sshpkt_disconnect (struct ssh*,char*,scalar_t__,scalar_t__) ; 

int
ssh_packet_read_expect(struct ssh *ssh, u_int expected_type)
{
	int r;
	u_char type;

	if ((r = ssh_packet_read_seqnr(ssh, &type, NULL)) != 0)
		return r;
	if (type != expected_type) {
		if ((r = sshpkt_disconnect(ssh,
		    "Protocol error: expected packet type %d, got %d",
		    expected_type, type)) != 0)
			return r;
		return SSH_ERR_PROTOCOL_ERROR;
	}
	return 0;
}