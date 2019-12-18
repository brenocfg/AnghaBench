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
struct mbufq {int mq_maxlen; int mq_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbufq_dequeue (struct mbufq*) ; 
 int /*<<< orphan*/  tcp_pcap_m_freem (int /*<<< orphan*/ ) ; 

void
tcp_pcap_set_sock_max(struct mbufq *queue, int newval)
{
	queue->mq_maxlen = newval;
	while (queue->mq_len > queue->mq_maxlen)
		tcp_pcap_m_freem(mbufq_dequeue(queue));
}