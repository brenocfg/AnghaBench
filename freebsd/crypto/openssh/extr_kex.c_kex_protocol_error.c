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
typedef  char* u_int32_t ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_UNIMPLEMENTED ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int sshpkt_put_u32 (struct ssh*,char*) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kex_protocol_error(int type, u_int32_t seq, struct ssh *ssh)
{
	int r;

	error("kex protocol error: type %d seq %u", type, seq);
	if ((r = sshpkt_start(ssh, SSH2_MSG_UNIMPLEMENTED)) != 0 ||
	    (r = sshpkt_put_u32(ssh, seq)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	return 0;
}