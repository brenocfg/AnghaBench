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
struct sock {scalar_t__ sk_protocol; } ;
struct chtls_listen {struct sock* sk; struct chtls_dev* cdev; } ;
struct chtls_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHTLS_LISTEN_STOP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPPROTO_TCP ; 
 struct chtls_listen* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_notify_list ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_mutex ; 
 int /*<<< orphan*/  raw_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct chtls_listen*) ; 

__attribute__((used)) static void chtls_stop_listen(struct chtls_dev *cdev, struct sock *sk)
{
	struct chtls_listen *clisten;

	if (sk->sk_protocol != IPPROTO_TCP)
		return;

	clisten = kmalloc(sizeof(*clisten), GFP_KERNEL);
	if (!clisten)
		return;
	clisten->cdev = cdev;
	clisten->sk = sk;
	mutex_lock(&notify_mutex);
	raw_notifier_call_chain(&listen_notify_list,
				CHTLS_LISTEN_STOP, clisten);
	mutex_unlock(&notify_mutex);
}