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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct chtls_hws {int mfs; int compute; int expansion; int fcplenmax; unsigned short pdus; int adjustlen; int tx_seq_no; } ;
struct chtls_sock {struct chtls_hws tlshws; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 void* chtls_expansion_size (struct sock*,int,int,unsigned short*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ tls_copy_ivs (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tls_copy_tx_key (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tls_tx_data_wr (struct sock*,struct sk_buff*,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void make_tlstx_data_wr(struct sock *sk, struct sk_buff *skb,
			       int tls_tx_imm, int tls_len, u32 credits)
{
	unsigned short pdus_per_ulp = 0;
	struct chtls_sock *csk;
	struct chtls_hws *hws;
	int expn_sz;
	int pdus;

	csk = rcu_dereference_sk_user_data(sk);
	hws = &csk->tlshws;
	pdus = DIV_ROUND_UP(tls_len, hws->mfs);
	expn_sz = chtls_expansion_size(sk, tls_len, 0, NULL);
	if (!hws->compute) {
		hws->expansion = chtls_expansion_size(sk,
						      hws->fcplenmax,
						      1, &pdus_per_ulp);
		hws->pdus = pdus_per_ulp;
		hws->adjustlen = hws->pdus *
			((hws->expansion / hws->pdus) + hws->mfs);
		hws->compute = 1;
	}
	if (tls_copy_ivs(sk, skb))
		return;
	tls_copy_tx_key(sk, skb);
	tls_tx_data_wr(sk, skb, tls_len, tls_tx_imm, credits, expn_sz, pdus);
	hws->tx_seq_no += (pdus - 1);
}