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
struct sock {scalar_t__ sk_protocol; scalar_t__ sk_family; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct chtls_listen {struct sock* sk; struct chtls_dev* cdev; } ;
struct chtls_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_rcv_saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHTLS_LISTEN_START ; 
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ LOOPBACK (int /*<<< orphan*/ ) ; 
 scalar_t__ PF_INET ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 struct chtls_listen* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_backlog_rcv ; 
 int /*<<< orphan*/  listen_notify_list ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_mutex ; 
 int raw_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct chtls_listen*) ; 

__attribute__((used)) static int chtls_start_listen(struct chtls_dev *cdev, struct sock *sk)
{
	struct chtls_listen *clisten;
	int err;

	if (sk->sk_protocol != IPPROTO_TCP)
		return -EPROTONOSUPPORT;

	if (sk->sk_family == PF_INET &&
	    LOOPBACK(inet_sk(sk)->inet_rcv_saddr))
		return -EADDRNOTAVAIL;

	sk->sk_backlog_rcv = listen_backlog_rcv;
	clisten = kmalloc(sizeof(*clisten), GFP_KERNEL);
	if (!clisten)
		return -ENOMEM;
	clisten->cdev = cdev;
	clisten->sk = sk;
	mutex_lock(&notify_mutex);
	err = raw_notifier_call_chain(&listen_notify_list,
				      CHTLS_LISTEN_START, clisten);
	mutex_unlock(&notify_mutex);
	return err;
}