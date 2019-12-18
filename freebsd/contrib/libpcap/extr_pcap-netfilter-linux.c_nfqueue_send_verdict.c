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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct nfqnl_msg_verdict_hdr {void* verdict; void* id; } ;
struct my_nfattr {int nfa_len; int /*<<< orphan*/  nfa_type; struct nfqnl_msg_verdict_hdr* data; } ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int NFNL_SUBSYS_QUEUE ; 
 int /*<<< orphan*/  NFQA_VERDICT_HDR ; 
 int NFQNL_MSG_VERDICT ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int netfilter_send_config_msg (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct my_nfattr*) ; 

__attribute__((used)) static int
nfqueue_send_verdict(const pcap_t *handle, uint16_t group_id, u_int32_t id, u_int32_t verdict)
{
	struct nfqnl_msg_verdict_hdr msg;
	struct my_nfattr nfa;

	msg.id = htonl(id);
	msg.verdict = htonl(verdict);

	nfa.data = &msg;
	nfa.nfa_type = NFQA_VERDICT_HDR;
	nfa.nfa_len = sizeof(msg);

	return netfilter_send_config_msg(handle, (NFNL_SUBSYS_QUEUE << 8) | NFQNL_MSG_VERDICT, 0, AF_UNSPEC, group_id, &nfa);
}