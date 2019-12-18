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
struct tid_info {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_family; } ;
struct chtls_sock {unsigned int tid; int /*<<< orphan*/  port_id; int /*<<< orphan*/ * l2t_entry; int /*<<< orphan*/ * txdata_skb_cache; struct chtls_dev* cdev; } ;
struct chtls_dev {struct tid_info* tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_l2t_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb4_remove_tid (struct tid_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void chtls_release_resources(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct chtls_dev *cdev = csk->cdev;
	unsigned int tid = csk->tid;
	struct tid_info *tids;

	if (!cdev)
		return;

	tids = cdev->tids;
	kfree_skb(csk->txdata_skb_cache);
	csk->txdata_skb_cache = NULL;

	if (csk->l2t_entry) {
		cxgb4_l2t_release(csk->l2t_entry);
		csk->l2t_entry = NULL;
	}

	cxgb4_remove_tid(tids, csk->port_id, tid, sk->sk_family);
	sock_put(sk);
}