#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_sha_rec {int flags; int /*<<< orphan*/  queue_task; TYPE_2__* req; } ;
struct mtk_cryp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int SHA_FLAGS_BUSY ; 
 int SHA_FLAGS_FINAL ; 
 scalar_t__ likely (int) ; 
 int mtk_sha_finish (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_sha_finish_req(struct mtk_cryp *cryp,
			       struct mtk_sha_rec *sha,
			       int err)
{
	if (likely(!err && (SHA_FLAGS_FINAL & sha->flags)))
		err = mtk_sha_finish(sha->req);

	sha->flags &= ~(SHA_FLAGS_BUSY | SHA_FLAGS_FINAL);

	sha->req->base.complete(&sha->req->base, err);

	/* Handle new request */
	tasklet_schedule(&sha->queue_task);
}