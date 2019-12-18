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
struct listen_info {unsigned int stid; struct listen_info* next; struct sock* sk; } ;
struct chtls_dev {int /*<<< orphan*/  listen_lock; struct listen_info** listen_hash_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct listen_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int listen_hashfn (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct listen_info *listen_hash_add(struct chtls_dev *cdev,
					   struct sock *sk,
					   unsigned int stid)
{
	struct listen_info *p = kmalloc(sizeof(*p), GFP_KERNEL);

	if (p) {
		int key = listen_hashfn(sk);

		p->sk = sk;
		p->stid = stid;
		spin_lock(&cdev->listen_lock);
		p->next = cdev->listen_hash_tab[key];
		cdev->listen_hash_tab[key] = p;
		spin_unlock(&cdev->listen_lock);
	}
	return p;
}