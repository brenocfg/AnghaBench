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
struct req_pkt {int /*<<< orphan*/  rm_vn_mode; } ;
struct recvbuf {int /*<<< orphan*/  recv_pkt; } ;

/* Variables and functions */
 int INFO_MODE (int /*<<< orphan*/ ) ; 

int
get_packet_mode(struct recvbuf *rbufp)
{
	struct req_pkt *inpkt = (struct req_pkt *)&rbufp->recv_pkt;
	return (INFO_MODE(inpkt->rm_vn_mode));
}