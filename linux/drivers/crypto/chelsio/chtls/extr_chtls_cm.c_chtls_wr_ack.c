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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_fw4_ack {int dummy; } ;
struct chtls_dev {int /*<<< orphan*/  tids; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GET_TID (struct cpl_fw4_ack*) ; 
 int RSS_HDR ; 
 int /*<<< orphan*/  chtls_rx_ack ; 
 struct cpl_fw4_ack* cplhdr (struct sk_buff*) ; 
 struct sock* lookup_tid (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  process_cpl_msg (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int chtls_wr_ack(struct chtls_dev *cdev, struct sk_buff *skb)
{
	struct cpl_fw4_ack *rpl = cplhdr(skb) + RSS_HDR;
	unsigned int hwtid = GET_TID(rpl);
	struct sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);
	if (unlikely(!sk)) {
		pr_err("can't find conn. for hwtid %u.\n", hwtid);
		return -EINVAL;
	}
	process_cpl_msg(chtls_rx_ack, sk, skb);

	return 0;
}