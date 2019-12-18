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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct chtls_dev {int /*<<< orphan*/  askb; struct chtls_dev* lldi; int /*<<< orphan*/ * rspq_skb_cache; int /*<<< orphan*/  hwtid_idr; TYPE_1__ kmap; int /*<<< orphan*/  tlsdev; } ;

/* Variables and functions */
 int RSPQ_HASH_BITS ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct chtls_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chtls_free_uld(struct chtls_dev *cdev)
{
	int i;

	tls_unregister_device(&cdev->tlsdev);
	kvfree(cdev->kmap.addr);
	idr_destroy(&cdev->hwtid_idr);
	for (i = 0; i < (1 << RSPQ_HASH_BITS); i++)
		kfree_skb(cdev->rspq_skb_cache[i]);
	kfree(cdev->lldi);
	kfree_skb(cdev->askb);
	kfree(cdev);
}