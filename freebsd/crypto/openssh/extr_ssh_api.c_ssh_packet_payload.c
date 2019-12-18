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
 int /*<<< orphan*/  const* sshpkt_ptr (struct ssh*,size_t*) ; 

const u_char *
ssh_packet_payload(struct ssh *ssh, size_t *lenp)
{
	return sshpkt_ptr(ssh, lenp);
}