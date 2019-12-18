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
struct tcpcb {int /*<<< orphan*/  t_outpkts; int /*<<< orphan*/  t_inpkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_tcp_pcap_packets ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tcp_pcap_tcpcb_init(struct tcpcb *tp)
{
	mbufq_init(&(tp->t_inpkts), V_tcp_pcap_packets);
	mbufq_init(&(tp->t_outpkts), V_tcp_pcap_packets);
}