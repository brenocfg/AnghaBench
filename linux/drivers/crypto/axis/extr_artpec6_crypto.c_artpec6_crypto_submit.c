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
struct artpec6_crypto_req_common {int /*<<< orphan*/  list; TYPE_1__* req; } ;
struct artpec6_crypto {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  pending; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  artpec6_crypto_busy () ; 
 int /*<<< orphan*/  artpec6_crypto_common_destroy (struct artpec6_crypto_req_common*) ; 
 int /*<<< orphan*/  artpec6_crypto_dev ; 
 int /*<<< orphan*/  artpec6_crypto_start_dma (struct artpec6_crypto_req_common*) ; 
 struct artpec6_crypto* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int artpec6_crypto_submit(struct artpec6_crypto_req_common *req)
{
	struct artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	int ret = -EBUSY;

	spin_lock_bh(&ac->queue_lock);

	if (!artpec6_crypto_busy()) {
		list_add_tail(&req->list, &ac->pending);
		artpec6_crypto_start_dma(req);
		ret = -EINPROGRESS;
	} else if (req->req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG) {
		list_add_tail(&req->list, &ac->queue);
	} else {
		artpec6_crypto_common_destroy(req);
	}

	spin_unlock_bh(&ac->queue_lock);

	return ret;
}