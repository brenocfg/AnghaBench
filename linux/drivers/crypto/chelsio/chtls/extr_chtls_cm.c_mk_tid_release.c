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
struct sk_buff {int dummy; } ;
struct cpl_tid_release {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_SETUP ; 
 int /*<<< orphan*/  CPL_TID_RELEASE ; 
 int /*<<< orphan*/  INIT_TP_WR_CPL (struct cpl_tid_release*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct cpl_tid_release*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int roundup (int,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static  void mk_tid_release(struct sk_buff *skb,
			    unsigned int chan, unsigned int tid)
{
	struct cpl_tid_release *req;
	unsigned int len;

	len = roundup(sizeof(struct cpl_tid_release), 16);
	req = (struct cpl_tid_release *)__skb_put(skb, len);
	memset(req, 0, len);
	set_wr_txq(skb, CPL_PRIORITY_SETUP, chan);
	INIT_TP_WR_CPL(req, CPL_TID_RELEASE, tid);
}