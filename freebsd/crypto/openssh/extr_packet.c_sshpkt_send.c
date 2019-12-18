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
struct TYPE_2__ {scalar_t__ mux; } ;

/* Variables and functions */
 int ssh_packet_send2 (struct ssh*) ; 
 int ssh_packet_send_mux (struct ssh*) ; 

int
sshpkt_send(struct ssh *ssh)
{
	if (ssh->state && ssh->state->mux)
		return ssh_packet_send_mux(ssh);
	return ssh_packet_send2(ssh);
}