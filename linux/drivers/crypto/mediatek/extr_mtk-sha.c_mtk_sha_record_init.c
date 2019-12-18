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
struct mtk_sha_rec {int /*<<< orphan*/  id; int /*<<< orphan*/  done_task; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; struct mtk_cryp* cryp; } ;
struct mtk_cryp {int rec; struct mtk_sha_rec** sha; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTK_REC_NUM ; 
 int /*<<< orphan*/  MTK_RING2 ; 
 int /*<<< orphan*/  MTK_RING3 ; 
 int /*<<< orphan*/  SHA_QUEUE_SIZE ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_sha_rec*) ; 
 struct mtk_sha_rec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sha_done_task ; 
 int /*<<< orphan*/  mtk_sha_queue_task ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mtk_sha_record_init(struct mtk_cryp *cryp)
{
	struct mtk_sha_rec **sha = cryp->sha;
	int i, err = -ENOMEM;

	for (i = 0; i < MTK_REC_NUM; i++) {
		sha[i] = kzalloc(sizeof(**sha), GFP_KERNEL);
		if (!sha[i])
			goto err_cleanup;

		sha[i]->cryp = cryp;

		spin_lock_init(&sha[i]->lock);
		crypto_init_queue(&sha[i]->queue, SHA_QUEUE_SIZE);

		tasklet_init(&sha[i]->queue_task, mtk_sha_queue_task,
			     (unsigned long)sha[i]);
		tasklet_init(&sha[i]->done_task, mtk_sha_done_task,
			     (unsigned long)sha[i]);
	}

	/* Link to ring2 and ring3 respectively */
	sha[0]->id = MTK_RING2;
	sha[1]->id = MTK_RING3;

	cryp->rec = 1;

	return 0;

err_cleanup:
	for (; i--; )
		kfree(sha[i]);
	return err;
}