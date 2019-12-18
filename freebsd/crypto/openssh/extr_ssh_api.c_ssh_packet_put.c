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
typedef  int /*<<< orphan*/  u_char ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int sshpkt_put (struct ssh*,int /*<<< orphan*/  const*,size_t) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int) ; 

int
ssh_packet_put(struct ssh *ssh, int type, const u_char *data, size_t len)
{
	int r;

	if ((r = sshpkt_start(ssh, type)) != 0 ||
	    (r = sshpkt_put(ssh, data, len)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	return 0;
}